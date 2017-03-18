//
// Created by ihoold on 17.03.17.
//

#ifndef ALGORITHMS_DINITZ_HPP
#define ALGORITHMS_DINITZ_HPP

#include "graph.hpp"
#include "bfs.hpp"

class DinitzNode : public BfsNode {

};

class DinitzEdge : public BfsEdge {
public:
    long long cap = 1;
    long long flt = 0;

    DinitzEdge(long long w) : cap(w) {};
};

template <typename Node, typename Edge>
long long Graph<Node, Edge>::V::findFlt(int dest, long long maxFlt) {
    if(this->index == dest || maxFlt <= 0L)
        return maxFlt;

    auto flt = 0L;
    for (auto& edge : childs) {
        if(!edge.disabled && edge.dest.dist == this->dist + 1) {
            auto currFlt = edge.dest.findFlt(dest, std::min(maxFlt, edge.cap - edge.flt));
            maxFlt -= currFlt;
            edge.flt += currFlt;
            if(edge.flt >= edge.cap)
                edge.disabled = true;
            edge.rev->flt -= currFlt;
            flt += currFlt;

            if (maxFlt <= 0)
                break;
        }
    }

    return flt;
};

template <typename Node, typename Edge>
long long Graph<Node, Edge>::dinitz(int source, int dest) {
    long long flt = 0;

    while(true) {
        for(auto& node : nodes)
            node.dist = INF;
        this->bfs(source);
        if (nodes[dest].dist == INF)
            return flt;

        flt += nodes[source].findFlt(dest, LONG_INF);
    }
};

#endif //ALGORITHMS_DINITZ_HPP
