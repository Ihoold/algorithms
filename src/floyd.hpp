//
// Created by ihoold on 05.03.17.
//

#ifndef ALGORITHMS_FLOYD_HPP
#define ALGORITHMS_FLOYD_HPP

#include "graph.hpp"
#include "dijkstra.hpp"

using FloydNode = DijkstraNode;
using FloydEdge = DijkstraEdge;


// Returns true if there is a cycle witch sums up to negative number.
template <typename Node, typename Edge>
bool Graph<Node, Edge>::floyd(int source) {
    this->nodes[source].dist = 0;
    auto comp = [](const std::pair<long long, int>& a,
                   const std::pair<long long, int>& b) {
        return (a.first == b.first) ? a.second < b.second : a.first < b.first;
    };
    std::set<std::pair<long long, int>, decltype(comp)> queue(comp);
    for (auto node : nodes)
        queue.insert(std::make_pair(node.dist, node.index));

    for (auto i = 0; i < this->nodes.size(); i++) {
        auto changed = false;

        for (auto node : this->nodes) {
            for(auto edge : node.childs) {
                auto updated_dist = node.dist + edge.weight;
                if (updated_dist < edge.dest.dist) {
                    changed = true;
                    queue.erase(std::make_pair(edge.dest.dist, edge.dest.index));
                    edge.dest.dist = updated_dist;
                    queue.insert(std::make_pair(edge.dest.dist, edge.dest.index));
                }
            }
        }

        if (!changed)
            return false;
    }

    return true;
};

#endif //ALGORITHMS_FLOYD_HPP
