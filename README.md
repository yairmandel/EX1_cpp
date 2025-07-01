
# Graph & Algorithms Project

This project implements the `Graph` class and the `Algorithms` class, which perform various algorithms on a specific graph.  
The graph is **weighted and undirected**, and it supports both positive and negative edge weights.

---

## Vertex Numbering

All vertices in the graph are indexed from `0` to `n-1`, where `n` is the number of vertices passed to the constructor.  
In all functions that receive or return vertex numbers, a valid vertex index must be within this range.

---

## Graph Class

This class represents the graph structure and provides basic operations on it.

### Functions:

- `addEdge` – Adds a valid edge between two different vertices.
- `removeEdge` – Removes the edge between two vertices.
- `getVertices` – Returns the number of vertices in the graph.
- `getNeighbors` – Returns neighbors and weights of a vertex.
- `print_graph` – Prints the graph using an adjacency list format.

---

## Helper Structures:

- `NodeQ` – Used in the queue implementation.
- `Edge` – Representing an edge (used in algorithms).

---

## Algorithms Class

This class implements several classic graph algorithms.

### Implemented Algorithms:

- `BFS` – Breadth-First Search.
- `DFS` – Depth-First Search (implemented recursively).
- `Dijkstra` – Shortest path algorithm (only supports graphs with non-negative weights).
- `Prim` – Minimum Spanning Tree (requires connected graph).
- `Kruskal` – Minimum Spanning Tree (requires connected graph).

---

## Error Handling

If there is an issue such as:

- Invalid start vertex
- Negative weights in Dijkstra
- The graph is not connected (for Prim or Kruskal)

Then the algorithm will return a graph with a single vertex.

---

## Helper Structures

- `NodeQ`
- `Queue` – Custom queue for BFS
- `UnionFind` – For Kruskal's algorithm

---

## Project Files

- `Graph.hpp` / `Graph.cpp` – Core graph data structure
- `Algorithms.hpp` / `Algorithms.cpp` – Algorithms implementation
- `main.cpp` – Demonstrates the execution of all algorithms on a sample graph.
- `test.cpp` – Contains tests for all algorithms, including edge cases.
- `Makefile` – Build and execution instructions

---

## Compile & Run

```bash
make Main         # Compiles and runs the main program
make test         # Runs the test suite
make valgrind     # Run test under valgrind to check memory leaks
make clean        # Remove compiled files
make main         # Compile only the main program
make test_exe     # Compile only the test suite
```
