#include <cstdio>

namespace Dinic {
    int n, s, t, max_flow;
    struct Node {
        std::vector<struct Edge> adj;
        struct Node *cur;
        int dist;
    } nodes[MAXV];
    struct Edge {
        Node* to;
        int cap, flow, rev;
        Edge(int to, int cap, int rev) to(to), cap(cap), flow(0), rev(rev) {}
    };
    void add_edge(int u, int v, int c) {
        nodes[u].adj.push_back(Edge(v, c, nodes[v].adj.size()));
        nodes[v].adj.push_back(Edge(u, 0, nodes[u].adj.size() - 1));
    }
    void bfs() {
        std::

    }
}
