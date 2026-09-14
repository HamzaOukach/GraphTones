## 🎨 GraphTones

Exploration of (a, b)-tone coloring on random and circulant graphs, with a constraint on decreasing color sharing based on the distance between vertices.

### Features
- (a, b)-tone coloring algorithm implementation using a greedy strategy
- Support for random graphs (G(n, p)) and circulant graphs
- Distance-based constraint on color sharing between vertices
- Benchmarking of minimum `a` (number of colors) needed for successful coloring, with execution time tracking

### Tech Stack
- **Language:** C++
- **IDE/Build:** Code::Blocks

### Getting Started

**Prerequisites:**
- Code::Blocks IDE (or any C++ compiler)

**Run the project:**

1. Clone the repository to your local machine

2. Open `projet2.cbp` in Code::Blocks and build/run the project.

### Usage

`main.cpp` contains three test modes. Only one is active by default; the other two are commented out and can be enabled by uncommenting the relevant block.

**1. Benchmark on random graphs (active by default)**
Runs the coloring algorithm across a range of vertex counts and color counts per vertex, searching for the minimum `a` (total colors) that yields a successful coloring, along with execution time:

```cpp
for (int n = 4; n <= 6; ++n) {
    for (int b = 1; b <= 2; ++b) {
        // finds minimal a and measures duration
    }
}
```

**2. Single graph test (commented out)**
Generates one random graph with fixed `n`, `a`, and `b` values, displays the graph and the generated color combinations, then applies the greedy tone-coloring algorithm once. Uncomment this block and set `n`, `a`, and `b` at the top of `main()` to use it.

**3. Circulant graph test (commented out)**
Generates a circulant graph `C_n(1, t)` instead of a random graph, then runs the same coloring and timing process. Uncomment this block (and the `genere_circulant(n, t)` call) to test on circulant graphs instead of random ones.
