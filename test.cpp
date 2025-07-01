#include <iostream>
#include <cassert>
#include "Graph.hpp"
#include "Algorithms.hpp"

using namespace graph;

void testBFS() {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    Graph bfsTree = Algorithms::bfs(g, 0);
    // bfsTree צריך להכיל את כל הקשתות שהובילו לביקור
    // בוא נבדוק שיש קשת בין 0 ל-1
    auto neighbors0 = bfsTree.getNeighbors(0);
    bool found = false;
    for (auto& n : neighbors0) {
        if (n.first == 1) {
            found = true;
            break;
        }
    }
    assert(found && "BFS test failed: edge 0->1 not found");
    std::cout << "BFS test passed.\n";
}

void testDFS() {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    Graph dfsTree = Algorithms::dfs(g, 0);
    // בדיקה דומה ל-BFS
    auto neighbors0 = dfsTree.getNeighbors(0);
    bool found = false;
    for (auto& n : neighbors0) {
        if (n.first == 1) {
            found = true;
            break;
        }
    }
    assert(found && "DFS test failed: edge 0->1 not found");
    std::cout << "DFS test passed.\n";
}

void testDijkstra() {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 3);
    g.addEdge(0, 2, 10);

    Graph dijkstraTree = Algorithms::dijkstra(g, 0);

    // בדיקה: הקשת הקצרה מ-0 ל-2 אמורה להיות דרך 1 (משקל 8 במקום 10)
    auto neighbors0 = dijkstraTree.getNeighbors(0);
    bool foundEdgeTo1 = false;
    for (auto& n : neighbors0) {
        if (n.first == 1) foundEdgeTo1 = true;
    }
    assert(foundEdgeTo1 && "Dijkstra test failed: no edge from 0 to 1");

    auto neighbors1 = dijkstraTree.getNeighbors(1);
    bool foundEdgeTo2 = false;
    for (auto& n : neighbors1) {
        if (n.first == 2) foundEdgeTo2 = true;
    }
    assert(foundEdgeTo2 && "Dijkstra test failed: no edge from 1 to 2");

    std::cout << "Dijkstra test passed.\n";
}

void testPrimAndKruskal() {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(2, 3, 2);

    Graph primMST = Algorithms::prim(g);
    Graph kruskalMST = Algorithms::kruskal(g);

    // MST של הגרף הוא 3 קשתות בסך הכל (n-1)
    assert(primMST.getNeighbors(0).size() + primMST.getNeighbors(1).size() +
           primMST.getNeighbors(2).size() + primMST.getNeighbors(3).size() >= 6 && "Prim MST test failed");

    assert(kruskalMST.getNeighbors(0).size() + kruskalMST.getNeighbors(1).size() +
           kruskalMST.getNeighbors(2).size() + kruskalMST.getNeighbors(3).size() >= 6 && "Kruskal MST test failed");

    std::cout << "Prim and Kruskal tests passed.\n";
}

int main() {
    try {
        testBFS();
        testDFS();
        testDijkstra();
        testPrimAndKruskal();
        std::cout << "All tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Test failed with unknown exception." << std::endl;
        return 1;
    }

    return 0;
}

