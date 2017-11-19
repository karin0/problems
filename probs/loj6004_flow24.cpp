#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int MAXV = 505;
const int INF = 2147483647;

namespace Dinic {
    int n, s, t, max_flow;
    struct Node {
        std::vector<struct Edge> adj;
        struct Edge* cur;
        int dist;
    } nodes[MAXV];
    struct Edge {
        Node* to;
        int cap, flow, rev;
        Edge(Node* to, int cap, int rev): to(to), cap(cap), flow(0), rev(rev) {}
    };
    inline void add_edge(int u, int v, int c) {
        nodes[u].adj.push_back(Edge(&nodes[v], c, nodes[v].adj.size()));
        nodes[v].adj.push_back(Edge(&nodes[u], 0, nodes[u].adj.size() - 1));
    }

    Node* que[MAXV];
    inline bool bfs() {
        int front = 1, back = 0;
        Node *u, *v;
        for (u = &nodes[1]; u <= &nodes[n]; ++u)
            u -> dist = 0;
        que[++back] = &nodes[s];
        nodes[s].dist = 1;
        
        while (front <= back) {
            u = que[front++];
            for (Edge *e = &(u -> adj.front()); e && e <= &(u -> adj.back()); ++e)
                if (!((v = e -> to) -> dist) && e -> cap > e -> flow)  {
                    v -> dist = u -> dist + 1;
                    que[++back] = v;
                }
        }
        return nodes[t].dist;
    }
    int dfs(Node* u, int a) {
        if (u == &nodes[t] || a == 0)
            return a;
        int res = 0, f;
        Node* v;
        for (Edge *&e = u -> cur; e && e <= &(u -> adj.back()); ++e) {
            v = e -> to;
            if (u -> dist + 1 == v -> dist && e -> cap > e -> flow && (f = dfs(v, std::min(a, e -> cap - e -> flow))) > 0) {
                res += f;
                a -= f;
                e -> flow += f;
                v -> adj[e -> rev].flow -= f;
                if (a == 0)
                    break;
            }
        }
        return res;
    }
    inline void dinic() {
        int i;
        Node *sp = &nodes[s], *u;
        while (bfs()) {
            for (i = 1; i <= n; ++i) {
                u = &nodes[i];
                u -> cur = &(u -> adj.front());
            }
            max_flow += dfs(sp, INF);
        }
    }
}

int n, m, sr;

int main() {
    scanf("%d%d", &n, &m);
    int i, j, v;
    Dinic::s = n + m + 1;
    Dinic::t = Dinic::s + 1;
    Dinic::n = Dinic::t;
    for (i = 1; i <= n; ++i) {
        scanf("%d", &v);
        sr += v;
        Dinic::add_edge(Dinic::s, i, v);
        for (j = n + 1; j <= n + m; ++j)
            Dinic::add_edge(i, j, 1);
    }
    for (i = 1; i <= m; ++i) {
        scanf("%d", &v);
        Dinic::add_edge(n + i, Dinic::t, v);
    }
    Dinic::dinic();
    if (Dinic::max_flow != sr) {
        printf("0\n");
        return 0;
    }
    printf("1\n");
    for (i = 1; i <= n; ++i) {
        for (Dinic::Edge *e = &(Dinic::nodes[i].adj.front()); e && e <= &(Dinic::nodes[i].adj.back()); ++e)
            if (e -> cap > 0 && e -> flow > 0)
                printf("%ld ", e -> to - Dinic::nodes - n);
        printf("\n");
    }


    return 0;
}
