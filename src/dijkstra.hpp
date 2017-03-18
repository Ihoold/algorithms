//
// Created by ihoold on 04.03.17.
//

#ifndef ALGORITHMS_DIJKSTRA_HPP
#define ALGORITHMS_DIJKSTRA_HPP

#include "graph.hpp"
#include <set>

class DijkstraNode : public Node {
public:
    long long dist = LONG_INF;
};

class DijkstraEdge : public Edge {
public:
    long long weight;

    DijkstraEdge(long long w) : weight(w) {};
};

template <typename Node, typename Edge>
void Graph<Node, Edge>::dijkstra(int source) {
    this->nodes[source].dist = 0;
    auto comp = [](const std::pair<long long, int>& a,
                   const std::pair<long long, int>& b) {
        return (a.first == b.first) ? a.second < b.second : a.first < b.first;
    };
    std::set<std::pair<long long, int>, decltype(comp)> queue(comp);
    for (auto node : nodes)
        queue.insert(std::make_pair(node.dist, node.index));

    while(!queue.empty()) {
        auto current = this->nodes[queue.begin()->second];
        queue.erase(queue.begin());
        for(auto edge : current.childs) {
            if(!edge.disabled) {
                auto updated_dist = current.dist + edge.weight;
                if (updated_dist < edge.dest.dist) {
                    queue.erase(std::make_pair(edge.dest.dist, edge.dest.index));
                    edge.dest.dist = updated_dist;
                    queue.insert(std::make_pair(edge.dest.dist, edge.dest.index));
                }
            }
        }
    }
};

#endif //ALGORITHMS_DIJKSTRA_HPP
