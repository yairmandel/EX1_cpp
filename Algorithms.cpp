#include "Algorithms.hpp"
#include <limits>
#include <stdexcept>

using namespace graph;

// Queue methods implementation 

void Queue::enqueue(int value) {
    NodeQ* newNode = new NodeQ(value);
    if (!rear) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

int Queue::dequeue() {
    if (!front) throw std::runtime_error("Queue is empty");
    NodeQ* temp = front;
    int val = temp->data;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
    return val;
}

//UnionFind methods implementation

UnionFind::UnionFind(int n) {
    parent = new int[n];
    rank = new int[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int UnionFind::find(int v) {
    if (parent[v] != v) {
        parent[v] = find(parent[v]);
    }
    return parent[v];
}

void UnionFind::union2roots(int v1, int v2) {
    int root1 = find(v1);
    int root2 = find(v2);
    if (root1 != root2) {
        if (rank[root1] < rank[root2]) {
            parent[root1] = root2;
        } else if (rank[root1] > rank[root2]) {
            parent[root2] = root1;
        } else {
            parent[root2] = root1;
            rank[root1]++;
        }
    }
}

//BFS

Graph Algorithms::bfs(const Graph& g, int start) {
    int n = g.getVertices();
    Graph result(n);
    bool* visited = new bool[n]();

    Queue q;
    q.enqueue(start);
    visited[start] = true;

    while (!q.isEmpty()) {
        int current = q.dequeue();

        for (auto& neighbor : g.getNeighbors(current)) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (!visited[v]) {
                visited[v] = true;
                q.enqueue(v);
                result.addEdge(current, v, w);
            }
        }
    }

    delete[] visited;
    return result;
}

//DFS

void dfsHelper(const Graph& g, int node, bool* visited, Graph& result) {
    visited[node] = true;

    for (auto& neighbor : g.getNeighbors(node)) {
        int v = neighbor.first;
        int w = neighbor.second;

        if (!visited[v]) {
            result.addEdge(node, v, w);
            dfsHelper(g, v, visited, result);
        }
    }
}

Graph Algorithms::dfs(const Graph& g, int start) {
    int n = g.getVertices();
    Graph result(n);
    bool* visited = new bool[n]();

    dfsHelper(g, start, visited, result);

    delete[] visited;
    return result;
}

// --- Dijkstra ---

Graph Algorithms::dijkstra(const Graph& g, int start) {
    int n = g.getVertices();
    int* dist = new int[n];
    int* prev = new int[n];
    bool* visited = new bool[n]();

    for (int i = 0; i < n; ++i) {
        dist[i] = std::numeric_limits<int>::max();
        prev[i] = -1;
    }
    dist[start] = 0;

    for (int i = 0; i < n; ++i) {
        int u = -1;
        int minDist = std::numeric_limits<int>::max();
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (auto& neighbor : g.getNeighbors(u)) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (!visited[v] && dist[u] != std::numeric_limits<int>::max() && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            }
        }
    }

    Graph result(n);
    for (int i = 0; i < n; ++i) {
        if (prev[i] != -1) {
            result.addEdge(prev[i], i, g.getNeighbors(prev[i])[0].second);
            // לא תמיד הגרף הוא כיווני, ולכן משתמשים במשקל המקורי
            // אפשר לשפר את החלק הזה במידה ויש פונקציה לקבלת משקל ישיר
            // אבל כרגע, נוסיף את הקשת עם המשקל מהגרף המקורי.
            // כדי לקבל את המשקל המדויק, נעבור על השכנים של prev[i] ונמצא את i
            // נממש את זה פה:
            int weight = 0;
            for (auto& nbr : g.getNeighbors(prev[i])) {
                if (nbr.first == i) {
                    weight = nbr.second;
                    break;
                }
            }
            result.addEdge(prev[i], i, weight);
        }
    }

    delete[] dist;
    delete[] prev;
    delete[] visited;
    return result;
}

// --- Prim ---

Graph Algorithms::prim(const Graph& g) {
    int n = g.getVertices();
    int* key = new int[n];
    int* parent = new int[n];
    bool* inMST = new bool[n]();

    for (int i = 0; i < n; ++i) {
        key[i] = std::numeric_limits<int>::max();
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < n - 1; ++count) {
        int u = -1;
        int minKey = std::numeric_limits<int>::max();

        for (int v = 0; v < n; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break;
        inMST[u] = true;

        for (auto& neighbor : g.getNeighbors(u)) {
            int v = neighbor.first;
            int w = neighbor.second;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
            }
        }
    }

    Graph result(n);
    for (int i = 1; i < n; ++i) {
        if (parent[i] != -1) {
            int weight = 0;
            for (auto& nbr : g.getNeighbors(parent[i])) {
                if (nbr.first == i) {
                    weight = nbr.second;
                    break;
                }
            }
            result.addEdge(parent[i], i, weight);
        }
    }

    delete[] key;
    delete[] parent;
    delete[] inMST;
    return result;
}

// --- Kruskal ---

struct Edge {
    int u, v, w;
};

Graph Algorithms::kruskal(const Graph& g) {
    int n = g.getVertices();
    UnionFind uf(n);

    // יוצרים מערך של קשתות מתוך הגרף
    std::vector<Edge> edges;

    for (int u = 0; u < n; ++u) {
        for (auto& neighbor : g.getNeighbors(u)) {
            int v = neighbor.first;
            int w = neighbor.second;
            if (u < v) { // כדי למנוע הכפלה (הגרף לא מכוון)
                edges.push_back({u, v, w});
            }
        }
    }

   
    for (size_t i = 0; i < edges.size(); ++i) {
        for (size_t j = i + 1; j < edges.size(); ++j) {
            if (edges[j].w < edges[i].w) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }

    Graph result(n);

    for (const Edge& e : edges) {
        if (uf.find(e.u) != uf.find(e.v)) {
            uf.union2roots(e.u, e.v);
            result.addEdge(e.u, e.v, e.w);
        }
    }

    return result;
}
