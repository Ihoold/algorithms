//
// Created by ihoold on 04.03.17.
//

#ifndef ALGORITHMS_DIJKSTRA_HPP
#define ALGORITHMS_DIJKSTRA_HPP

#include "graph.hpp"
#include <set>

const int LONG_INF = 10e16;

class DijkstraNode : public Node {
public:
    long long dist = INF;
};

class DijkstraEdge : public Edge {
public:
    long long weight;

    DijkstraEdge(long long w) : weight(w) {};
};

template <typename Node, typename Edge>
void Graph<Node, Edge>::dijkstra(int source) {
    this->nodes[source].dist = 0;
    auto comp = [](pair<long long, int>& a, pair<long long, int>& b) {
        return (a.first == b.first) ? a.second < b.second : a.first < b.first;
    };
    set<pair<long long, int>> queue(comp);
    for (auto node : nodes)
        queue.insert(make_pair(node.dist, node.index));

    while(!queue.empty()) {
        auto current = this->nodes[queue.begin()->second];
        for(auto edge : current.childs) {
            auto updated_weight = current.dist + edge.dest.weight;
            if (updated_weight < edge.dest.weight) {
                queue.erase(make_pair(edge.dest.weight, edge.dest.index));
                queue.insert(make_pair(updated_weight, edge.dest.index));
            }
        }
    }
};

#endif //ALGORITHMS_DIJKSTRA_HPP
