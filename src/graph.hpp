#ifndef ALGORITHMS_GRAPH_HPP
#define ALGORITHMS_GRAPH_HPP

#include <vector>
#include <deque>
#include <iostream>


class Node{};
class Edge {};

template <typename Node, typename Edge>
class Graph {
public:
    class V;
    class E : public Edge {
    public:
        V& dest;

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
    void addEdge(int source, int dest) {
        nodes[source].childs.emplace_back(nodes[dest]);
    }

    void addEdge(int source, int dest, Edge toAdd) {
        nodes[source].childs.emplace_back(nodes[dest], std::move(toAdd));
    }

    void addDoubleEdge(int source, int dest) {
        nodes[source].childs.emplace_back(nodes[dest]);
        nodes[dest].childs.emplace_back(nodes[source]);
    }

    void addDoubleEdge(int source, int dest, Edge toAdd) {
        nodes[source].childs.emplace_back(nodes[dest], toAdd);
        nodes[dest].childs.emplace_back(nodes[source], std::move(toAdd));
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


    void dfs();
    void bfs(int source = 0);
};

#endif //ALGORITHMS_DFS_HPP