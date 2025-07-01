// Graph.cpp
#include "Graph.hpp"
#include <iostream>

namespace graph {

Graph::Graph(int vertices) : numVertices(vertices), adjList(vertices) {
    
}

void Graph::addEdge(int source, int destination, int weight) {
    if (source >= numVertices || destination >= numVertices) {
        throw std::out_of_range("Vertex index out of range.");
    }
    adjList[source].push_back({destination, weight});
    adjList[destination].push_back({source, weight});
}

void Graph::removeEdge(int source, int destination) {
    bool found = false;

    
    auto& neighbors = adjList[source];  
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
        if (it->first == destination) {  
            neighbors.erase(it);         
            found = true;
            break;
        }
    }

    if (!found) {
        throw std::runtime_error("Edge from source to destination not found.");
    }

   
    found = false;
    auto& neighbors2 = adjList[destination];  
    for (auto it = neighbors2.begin(); it != neighbors2.end(); ++it) {
        if (it->first == source) {  
            neighbors2.erase(it); 
            found = true;
            break;
        }
    }

    if (!found) {
        throw std::runtime_error("Edge from destination to source not found.");
    }
}



void Graph::print_graph() const {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Vertex " << i << ": ";
        for (const auto& neighbor : adjList[i]) {
            std::cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        std::cout << std::endl;
    }
}
int Graph::getVertices() const {
    return numVertices;
}
const std::vector<std::pair<int, int>>& Graph::getNeighbors(int v) const {
    if (v >= numVertices) {
        throw std::out_of_range("Vertex index out of range.");
    }
    return adjList[v];
}
}
