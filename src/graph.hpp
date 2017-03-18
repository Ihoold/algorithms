#ifndef ALGORITHMS_GRAPH_HPP
#define ALGORITHMS_GRAPH_HPP

#include <vector>
#include <deque>
#include <iostream>


const int INF = 10e8;
const long long LONG_INF = 10e16;


class Node {};
class Edge {
public:
    bool disabled = false;
};


template <typename Node, typename Edge>
class Graph {
public:
    class V;
    class E : public Edge {
    public:
        V& dest;
        E* rev = nullptr;

        E(V& dest) : dest(dest) {};
        E(V& dest, Edge& info) : Edge(info), dest(dest){}
        E(V& dest, Edge&& info) : Edge(std::move(info)), dest(dest){}
    };

    class V : public Node {
    public:
        std::vector<E> childs;
        unsigned int index;

        V() = default;
        V(unsigned int index) : index(index) {};
        V(unsigned int index, Node&& info) : Node(std::move(info)), index(index) {};

        int dfs(int time);
        void bfs(std::deque<int>& toVisit);
        long long findFlt(int dest, long long maxFlt);
    };

    // Attributes
    std::vector<V> nodes;

    // Constructors
    Graph() = default;
    Graph(int n) : nodes(n) {
        for (int i = 0; i < n; i++)
            nodes[i].index = i;
    }

    // Utilities
    V& addNode() {
        nodes.emplace_back(nodes.size());
        return nodes.back();
    }

    V& addNode(Node&& info) {
        nodes.emplace_back(nodes.size(), std::move(info));
        return nodes.back();
    }

    void addEdge(int source, int dest) {
        nodes[source].childs.emplace_back(nodes[dest]);
    }

    void addEdge(int source, int dest, Edge toAdd) {
        nodes[source].childs.emplace_back(nodes[dest], std::move(toAdd));
    }

    void addDoubleEdge(int source, int dest) {
        nodes[source].childs.emplace_back(nodes[dest]);
        nodes[dest].childs.emplace_back(nodes[source]);
        nodes[source].childs.back().rev = &nodes[dest].childs.back();
        nodes[dest].childs.back().rev = &nodes[source].childs.back();
    }

    void addDoubleEdge(int source, int dest, Edge toAdd) {
        nodes[source].childs.emplace_back(nodes[dest], toAdd);
        nodes[dest].childs.emplace_back(nodes[source], std::move(toAdd));
        nodes[source].childs.back().rev = &nodes[dest].childs.back();
        nodes[dest].childs.back().rev = &nodes[source].childs.back();
    }

    void print() {
        for (auto node : nodes) {
            std::cout << node.index << ": ";
            for (auto edge : node) {
                std::cout << edge.dest.index << " ";
            }
            std::cout << std::endl;
        }
    }

    void dfs(int source = -1);
    void bfs(int source = 0);
    void dijkstra(int source = 0);
    // Returns true if there is a cycle witch sums up to negative number.
    bool floyd(int source = 0);
    long long dinitz(int source, int dest);
};

#endif //ALGORITHMS_DFS_HPP