#include "../src/graph.hpp"
#include "../src/dfs.hpp"
#include "../src/bfs.hpp"
#include "../src/dijkstra.hpp"
#include "../src/floyd.hpp"

#include <fstream>
#include <assert.h>

using namespace std;

void constructor_tests() {
    Graph<Node, Edge> g1;
    Graph<Node, Edge> g2(10);
    cout << "success." << endl;
}

void utilites_tests() {
    Graph<Node, Edge> g1(10);
    g1.addEdge(0, 1);
    g1.addDoubleEdge(1, 0);
    cout << "success." << endl;
}

void loading_graph_test() {
    ifstream file("/home/ihoold/git/programming/algorithms/tests/example_graph");
    int n, m;
    file >> n >> m;
    Graph<Node, Edge> g1(n);
    int fst, snd;
    for (auto i = 0; i < m; i++) {
        file >> fst >> snd;
        g1.addDoubleEdge(fst, snd);
    }
    cout << "success." << endl;
}


class Edge_ : public Edge {
public:
    int i;
    Edge_(int i) : i(i) {};
};

void more_info_test() {
    ifstream file("/home/ihoold/git/programming/algorithms/tests/example_graph");
    int n, m;
    file >> n >> m;
    Graph<Node, Edge> g1(n);
    int fst, snd;
    for (auto i = 0; i < m; i++) {
        file >> fst >> snd;
        g1.addDoubleEdge(fst, snd, Edge_(i));
    }
    cout << "success." << endl;
}

void dfs_test() {
    ifstream file("/home/ihoold/git/programming/algorithms/tests/example_graph");
    int n, m;
    file >> n >> m;
    Graph<DfsNode, Edge> g1(n);
    int fst, snd;
    for (auto i = 0; i < m; i++) {
        file >> fst >> snd;
        g1.addDoubleEdge(fst, snd);
    }
    g1.dfs();

    assert(g1.nodes[0].in == 1 && g1.nodes[0].out == 20);
    cout << "success." << endl;
}

void bfs_test() {
    ifstream file("/home/ihoold/git/programming/algorithms/tests/example_graph");
    int n, m;
    file >> n >> m;
    Graph<BfsNode, Edge> g1(n);
    int fst, snd;
    for (auto i = 0; i < m; i++) {
        file >> fst >> snd;
        g1.addDoubleEdge(fst, snd);
    }
    g1.bfs();

    cout << "success." << endl;
}

void dijkstra_test() {
    ifstream file("/home/ihoold/git/programming/algorithms/tests/example_graph2");
    int n, m;
    file >> n >> m;
    Graph<DijkstraNode, DijkstraEdge> g1(n);
    int fst, snd;
    long long rd;
    for (auto i = 0; i < m; i++) {
        file >> fst >> snd >> rd;
        g1.addDoubleEdge(fst, snd, DijkstraEdge(rd));
    }
    g1.dijkstra();

    cout << "success." << endl;
}

void floyd_positive_test() {
    ifstream file("/home/ihoold/git/programming/algorithms/tests/example_graph2");
    int n, m;
    file >> n >> m;
    Graph<FloydNode, FloydEdge> g1(n);
    int fst, snd;
    long long rd;
    for (auto i = 0; i < m; i++) {
        file >> fst >> snd >> rd;
        g1.addDoubleEdge(fst, snd, FloydEdge(rd));
    }

    assert (!g1.floyd());
    cout << "success." << endl;
}


void floyd_negative_test() {
    ifstream file("/home/ihoold/git/programming/algorithms/tests/example_graph3");
    int n, m;
    file >> n >> m;
    Graph<FloydNode, FloydEdge> g1(n);
    int fst, snd;
    long long rd;
    for (auto i = 0; i < m; i++) {
        file >> fst >> snd >> rd;
        g1.addDoubleEdge(fst, snd, FloydEdge(rd));
    }

    assert (g1.floyd());
    cout << "success." << endl;
}

int main() {
    cout << "Constructor tests: ";
    constructor_tests();

    cout << "Utilities tests: ";
    utilites_tests();

    cout << "Loading example graph: ";
    loading_graph_test();

    cout << "More info graph: ";
    more_info_test();

    cout << "Dfs test: ";
    dfs_test();

    cout << "Bfs test: ";
    bfs_test();

    cout << "Dijkstra test: ";
    dijkstra_test();

    cout << "Floyd test 1: ";
    floyd_positive_test();

    cout << "Floyd test 2: ";
    floyd_negative_test();
}