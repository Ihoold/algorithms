//
// Created by ihoold on 04.03.17.
//

#ifndef ALGORITHMS_DFS_HPP
#define ALGORITHMS_DFS_HPP

#include "graph.hpp"

class DfsNode : public Node {
public:
    int in = 0;
    int out = 0;
};

class DfsEdge : public Edge {

};

template <typename Node, typename Edge>
int Graph<Node, Edge>::V::dfs(int time) {
    this->in = time++;
    for (auto edge : childs) {
        if (!edge.disabled && edge.dest.in == 0)
            time = edge.dest.dfs(time);
    }
    this->out = time++;
    return time;
};

template <typename Node, typename Edge>
void Graph<Node, Edge>::dfs(int source) {
    if(source != -1) {
        nodes[source].dfs(1);
        return;
    }
    auto time = 1;
    for (auto& node : nodes) {
        if (node.in == 0)
            time = node.dfs(time);
    }
};

#endif //ALGORITHMS_DFS_HPP
