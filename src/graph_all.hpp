//
// Created by ihoold on 18.03.17.
//

#ifndef ALGORITHMS_GRAPH_ALL_HPP
#define ALGORITHMS_GRAPH_ALL_HPP

#include <vector>
#include <deque>
#include <set>
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

        int dfs(int time) {
            this->in = time++;
            for (auto edge : childs) {
                if (!edge.disabled && edge.dest.in == 0)
                    time = edge.dest.dfs(time);
            }
            this->out = time++;
            return time;
        }

        void bfs(std::deque<int>& toVisit) {
            for (auto edge : this->childs) {
                if (!edge.disabled && !edge.dest.visited) {
                    edge.dest.visited = true;
                    edge.dest.dist = this->dist + 1;
                    toVisit.push_back(edge.dest.index);
                }
            }
        }

        long long findFlt(int dest, long long maxFlt) {
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
        }
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

    void dfs(int source = -1) {
        if(source != -1) {
            nodes[source].dfs(1);
            return;
        }
        auto time = 1;
        for (auto& node : nodes) {
            if (node.in == 0)
                time = node.dfs(time);
        }
    }

    void bfs(int source = 0) {
        std::deque<int> toVisit;
        this->nodes[source].dist = 0;
        this->nodes[source].visited = true;
        this->nodes[source].bfs(toVisit);
        while(!toVisit.empty()) {
            auto next = toVisit.front();
            toVisit.pop_front();
            this->nodes[next].bfs(toVisit);
        }
    }

    void dijkstra(int source = 0) {
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
    }
    // Returns true if there is a cycle witch sums up to negative number.
    bool floyd(int source = 0) {
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
                    if(!edge.disabled) {
                        auto updated_dist = node.dist + edge.weight;
                        if (updated_dist < edge.dest.dist) {
                            changed = true;
                            queue.erase(std::make_pair(edge.dest.dist, edge.dest.index));
                            edge.dest.dist = updated_dist;
                            queue.insert(std::make_pair(edge.dest.dist, edge.dest.index));
                        }
                    }
                }
            }

            if (!changed)
                return false;
        }

        return true;
    }

    long long dinitz(int source, int dest) {
        long long flt = 0;

        while(true) {
            for(auto& node : nodes)
                node.dist = INF;
            this->bfs(source);
            if (nodes[dest].dist == INF)
                return flt;

            flt += nodes[source].findFlt(dest, LONG_INF);
        }
    }
};

class BfsNode : public Node {
public:
    int dist = INF;
    bool visited = false;
};

class BfsEdge : public Edge {

};

class DfsNode : public Node {
public:
    int in = 0;
    int out = 0;
};

class DfsEdge : public Edge {

};

class DijkstraNode : public Node {
public:
    long long dist = LONG_INF;
};

class DijkstraEdge : public Edge {
public:
    long long weight;

    DijkstraEdge(long long w) : weight(w) {};
};

class DinitzNode : public BfsNode {

};

class DinitzEdge : public BfsEdge {
public:
    long long cap = 1;
    long long flt = 0;

    DinitzEdge(long long w) : cap(w) {};
};

using FloydNode = DijkstraNode;
using FloydEdge = DijkstraEdge;


#endif //ALGORITHMS_GRAPH_ALL_HPP
