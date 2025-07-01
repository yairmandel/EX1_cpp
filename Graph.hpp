#pragma once
#include <vector>
#include <stdexcept>

namespace graph {

class Graph {
private:
    int numVertices;
    std::vector<std::vector<std::pair<int, int>>> adjList;

public:
    Graph(int vertices);
    void addEdge(int src, int dest, int weight = 1);
    void removeEdge(int src, int dest);
    void print_graph() const;
    int getVertices() const;
    const std::vector<std::pair<int, int>> & getNeighbors(int v) const;
};

}