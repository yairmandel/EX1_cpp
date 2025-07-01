#include <iostream>
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace graph;

int main() {
    // יצירת גרף עם 6 קודקודים (0-5)
    Graph g(6);

    // הוספת קשתות (מקור, יעד, משקל)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    g.addEdge(0, 3, 1);

    Graph p(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    

    std::cout << "Original Graph:" << std::endl;
    g.print_graph();

    g.removeEdge(0, 3);

    std::cout << "Original Graph:" << std::endl;
    g.print_graph();

    // bfs 
    Graph bfsGraph = Algorithms::bfs(g, 0);
    std::cout << "\nBFS tree from vertex 0:" << std::endl;
    bfsGraph.print_graph();

    // dfs 
    Graph dfsGraph = Algorithms::dfs(g, 0);
    std::cout << "\nDFS tree from vertex 0:" << std::endl;
    dfsGraph.print_graph();

    // דייקסטרה
    Graph dijkstraGraph = Algorithms::dijkstra(g, 0);
    std::cout << "\nDijkstra shortest paths from vertex 0:" << std::endl;
    dijkstraGraph.print_graph();

    Graph dijkstraGraph2 = Algorithms::dijkstra(p, 0);
    std::cout << "\nDijkstra shortest paths from vertex 0:" << std::endl;
    dijkstraGraph.print_graph();

    // Prim - MST
    Graph primGraph = Algorithms::prim(g);
    std::cout << "\nPrim MST:" << std::endl;
    primGraph.print_graph();

    // Kruskal - MST
    Graph kruskalGraph = Algorithms::kruskal(g);
    std::cout << "\nKruskal MST:" << std::endl;
    kruskalGraph.print_graph();

    return 0;
}

