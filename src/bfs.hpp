//
// Created by ihoold on 04.03.17.
//

#ifndef ALGORITHMS_BFS_HPP
#define ALGORITHMS_BFS_HPP

#include "graph.hpp"
#include <deque>

class BfsNode : public Node {
public:
    int dist = INF;
    bool visited = false;
};

class BfsEdge : public Edge {

};


template <typename Node, typename Edge>
void Graph<Node, Edge>::V::bfs(std::deque<int>& toVisit) {
    for (auto edge : this->childs) {
        if (!edge.disabled && !edge.dest.visited) {
            edge.dest.visited = true;
            edge.dest.dist = this->dist + 1;
            toVisit.push_back(edge.dest.index);
        }
    }
}

template <typename Node, typename Edge>
void Graph<Node, Edge>::bfs(int source) {
    std::deque<int> toVisit;
    this->nodes[source].dist = 0;
    this->nodes[source].visited = true;
    this->nodes[source].bfs(toVisit);
    while(!toVisit.empty()) {
        auto next = toVisit.front();
        toVisit.pop_front();
        this->nodes[next].bfs(toVisit);
    }
};

#endif //ALGORITHMS_BFS_HPP
