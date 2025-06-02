#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <chrono>

using namespace std;

#define MAX_N 100
const int MAX_COL = 100; // nombre de sommets
int adj[MAX_N][MAX_N];
int couleur2[MAX_N][MAX_COL];
const int MAX_K = 100;
const int MAX_COMB = 1000;
int combinaisons[MAX_COMB][10];
int nbComb = 0;
int taille_couleur[MAX_N];


void generegraphe(int p, int n)
{
    srand(time(0));

    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            if ((rand() % 100) < p) {
                adj[i][j] = adj[j][i] = 1;
            } else {
                adj[i][j] = adj[j][i] = 0;
            }
        }

    for (int i = 0; i < n; i++)
        adj[i][i] = 0;
}

// BFS pour calculer la distance entre deux sommets
int distance(int start, int end, int n)
{
    if (start == end) return 0;

    vector<bool> visited(n, false);
    vector<int> dist(n, -1);
    vector<int> queue;

    queue.push_back(start);
    visited[start] = true;
    dist[start] = 0;

    while (!queue.empty()) {
        int curr = queue.front();
        queue.erase(queue.begin());

        for (int i = 0; i < n; i++) {
            if (adj[curr][i] && !visited[i]) {
                visited[i] = true;
                dist[i] = dist[curr] + 1;
                if (i == end) return dist[i];
                queue.push_back(i);
            }
        }
    }

    return n + 1; // s'ils ne sont pas connectés
}

void generateCombinations(int a, int b, int start = 1, int depth = 0, int current[] = nullptr)
{
    static int temp[10]; // tableau temporaire pour stocker une combinaison

    if (current == nullptr)
        current = temp;

    if (depth == b)
    {
        // copie des combinaison dans le tableau global
        for (int i = 0; i < b; i++)
            combinaisons[nbComb][i] = current[i];
        nbComb++;
        return;
    }

    for (int i = start; i <= a; i++)
    {
        current[depth] = i;
        generateCombinations(a, b, i + 1, depth + 1, current);
    }
}

bool contient(int tab[], int taille, int val)
{
    for (int i = 0; i < taille; i++)
        if (tab[i] == val)
            return true;
    return false;
}

bool convient_par_tons(int x, int colors[], int b, int k, int n)
{
    cout << "\nVerification de la combinaison [ ";
    for (int j = 0; j < b; j++) cout << colors[j] << " ";
    cout << "] pour sommet " << x << endl;

    for (int y = 0; y < n   ; y++)
    {
        if (y == x) continue;

        if (taille_couleur[y] == 0) {
            cout << "sommet " << y << " ignore (non colorie)" << endl;
            continue;
        }

        int d = distance(x, y, n);
        cout << "distance(" << x << ", " << y << ") = " << d << endl;

        if (d == 0) {
            cout << " Rejet immediat : distance nulle avec soi-meme" << endl;
            return false;
        }

        if (d >= n) {
            cout << "Rejet : sommet " << x << " n'est pas connecte a " << y << ", distance >= n aucun partage permis" << endl;
            return false;
        }

        int commun = 0;
        for (int i = 0; i < b; i++) {
            if (contient(couleur2[y], taille_couleur[y], colors[i]))
                commun++;
        }

        int partage_max = k / d;
        cout << "partage max autorise : " << partage_max<< endl;


        if (commun > partage_max) {
            cout << "Rejet : la combinaison partage " << commun << " couleur(s) avec " << y
                 << " (distance = " << d << "), limite = " << partage_max << endl;
            return false;
        }
    }

    cout << "Acceptee pour sommet " << x << endl;
    return true;
}




bool ColorationGloutonne(int b, int k, int n, int& maxColor)
{
    maxColor = 0;
    for (int i = 0; i < n; i++)
        taille_couleur[i] = 0;

    for (int x = 0; x < n; x++)
    {
        bool trouve = false;
        for (int i = 0; i < nbComb && !trouve; i++)
        {
            cout << "Test de la combinaison numero " << i + 1 << " pour le sommet " << x << endl;

            if (convient_par_tons(x, combinaisons[i], b, k, n))
            {
                for (int j = 0; j < b; j++) {
                    couleur2[x][j] = combinaisons[i][j];
                    if (couleur2[x][j] > maxColor)
                        maxColor = couleur2[x][j];
                }
                taille_couleur[x] = b;
                cout << "Sommet " << x << " colorie avec : ";
                for (int j = 0; j < b; j++)
                    cout << couleur2[x][j] << " ";
                cout << endl;
                trouve = true;
            }
        }

        if (!trouve)
            return false; // échec : au moins un sommet non colorié
    }

    for (int i = 0; i < n; i++) {
        cout << "sommet " << i << " : ";
        for (int j = 0; j < taille_couleur[i]; j++) {
            cout << couleur2[i][j] << " ";
        }
        cout << endl;
    }

    return true; // succès : tous les sommets sont coloriés
}



void affichegraphe(int n)
{
    for (int i = 0; i < n; i++) {
        cout << "sommet " << i << " : ";
        for (int j = 0; j < n; j++)
            if (adj[i][j]) cout << j << " ";
        cout << endl;
    }
}

void genere_circulant(int n, int t)
{

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            adj[i][j] = 0;

    for (int i = 0; i < n; ++i)
    {
        int voisin1 = (i + 1) % n;
        int voisin2 = (i - 1 + n) % n;
        int voisin3 = (i + t) % n;
        int voisin4 = (i - t + n) % n;

        adj[i][voisin1] = adj[voisin1][i] = 1;
        adj[i][voisin2] = adj[voisin2][i] = 1;
        adj[i][voisin3] = adj[voisin3][i] = 1;
        adj[i][voisin4] = adj[voisin4][i] = 1;
    }

    cout << "\n Graphe circulant C_" << n << "(1," << t << ") genere :\n";
    for (int i = 0; i < n; i++) {
        cout << "sommet " << i << " : ";
        for (int j = 0; j < n; j++)
            if (adj[i][j]) cout << j << " ";
        cout << endl;
    }
}


int main()
{
    //int n = 7;     // Nombre de sommets (à décommenter pour tester sur un seul graphe )
    //int a = 3;     // Nombre total de couleurs disponibles (à décommenter pour tester sur un seul graphe )
    //int b = 2;     // Nombre de couleurs par sommet (à décommenter pour tester sur un seul graphe )
    int k = 2;     // Partage maximal
    int t = 3;     // Saut pour le graphe circulant
    int p = 50;    // Probabilité d’avoir une arête dans G(n, p)
    int maxColor;
    int max_a = 10;

    // Génération d'un seul graphe
    // Première étape : Générer les combinaisons possibles
    /*generateCombinations(a, b);

    cout << "Combinaisons de " << b << " couleurs parmi 1 a " << k << " :\n";
    for (int i = 0; i < nbComb; i++) {
        cout << i + 1 << ". ";
        for (int j = 0; j < b; j++)
            cout << combinaisons[i][j] << " ";
        cout << endl;
    }

    // Deuxième étape : Générer un graphe aléatoire ( à commenter pour tester le graphe circulant )
    generegraphe(p, n);

    cout << "Graphe genere (G(" << n << ", " << p << "%)) :\n";
    affichegraphe(n);

    // Graphe circulant
    //genere_circulant(n, t);

    // Troisème étape : Appliquer la coloration gloutonne par tons
    bool success = ColorationGloutonne(b, k, n, maxColor);

    if (success)
        cout << "Coloration reussie avec maxColor = " << maxColor << endl;
    else
        cout << "Echec de la coloration" << endl;*/

    // Test avec des Graphes aléatoires

    for (int n = 4; n <= 6; ++n) {
        for (int b = 1; b <= 2; ++b) {
            bool success = false;
            int a_min = -1;
            long long duration = 0;

            for (int a = b; a <= max_a; ++a) { // a doit être ≥ b
                nbComb = 0;
                generateCombinations(a, b);
                generegraphe(p, n);
                auto start = chrono::high_resolution_clock::now();
                success = ColorationGloutonne(b, k, n, maxColor);
                auto end = chrono::high_resolution_clock::now();
                duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

                if (success) {
                    a_min = a;
                    break;
                }
            }

            if (success)
                cout << "Nombre de sommets " << n << "  |  Nombre de couleurs par sommet " << b << "  |   la valeur de a obtenue " << a_min
                     << "     |   " << duration << " ms\n";
            else
                cout << " Nombre de sommets " << n << "  |  Nombre de couleurs par sommet " << b << "  |   echec   |           -           |   " << duration << " ms\n";
        }
    }

    //Code pour le test des graphes ciruclants
       /* nbComb = 0;
        generateCombinations(a, b);
        genere_circulant(n, t);

        auto start = chrono::high_resolution_clock::now();
        int couleursUtilisees = ColorationGloutonne(b,k, n, maxColor);
        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        cout << "nombre de sommets " << n << " | couleurs utilisees " << couleursUtilisees << " | " << duration << " ms" << endl;*/







    return 0;
}


