// Algorithms.hpp
#pragma once
#include "Graph.hpp"

struct NodeQ{
    int data;
    NodeQ* next;
    NodeQ(int d) : data(d), next(nullptr){}
};
class Queue {
    private:
        NodeQ *front , *rear;
    public:
    Queue() : front(nullptr), rear(nullptr){}

    void enqueue(int value);
    int dequeue();
    bool isEmpty(){return front == nullptr;}
};
class UnionFind {
private:
    int* parent;
    int* rank;
public:
    UnionFind(int n);
    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }    
    int find(int v);
    void union2roots(int v1, int v2);
};

namespace graph {

class Algorithms {
public:
    static Graph bfs(const Graph& g, int start);
    static Graph dfs(const Graph& g, int start);
    static Graph dijkstra(const Graph& g, int start);
    static Graph prim(const Graph& g);
    static Graph kruskal(const Graph& g);
};

}