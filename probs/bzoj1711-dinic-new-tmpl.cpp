#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>

const int N = 103, INF = INT_MAX;
namespace G {
    int n;
    struct Node {
        struct Edge *e, *cur;
        int lvl;
    } g[N * 4], *s, *t;
    struct Edge {
        Node *v;
        int cap, flow;
        Edge *e, *rev;
        Edge (Node *_u, Node *_v, int _c, Edge *_r = NULL) : v(_v), cap(_c), flow(0), e(_u->e), rev(_r ? _r : new Edge(_v, _u, 0, this)) {
            _u->e = this;
        }
    };
    bool bfs() {
        for (int i = 1; i <= n; ++i)
            g[i].lvl = 0, g[i].cur = g[i].e;
        std::queue<Node *> q;
        s->lvl = 1;
        q.push(s);
        while (!q.empty()) {
            Node *u = q.front(), *v;
            q.pop();
            for (Edge *e = u->e; e; e = e->e)
                if (e->cap > e->flow && (v = e->v)->lvl == 0) {
                    v->lvl = u->lvl + 1;
                    if (v == t)
                        return true;
                    q.push(v);
                }
        }
        return false;
    }
    int dfs(Node *u, int lim) {
        if (u == t || lim == 0)
            return lim;
        int res = 0, f;
        for (Edge *&e = u->cur; e; e = e->e)
            if (e->cap > e->flow && e->v->lvl == u->lvl + 1 && (f = dfs(e->v, std::min(lim, e->cap - e->flow))) > 0) {
                e->flow += f;
                e->rev->flow -= f;
                res += f;
                lim -= f;
                if (lim == 0)
                    break;
            }
        return res;
    }
    int dinic() {
        int res = 0;
        while (bfs())
            res += dfs(s, INF);
        return res;
    }
}
using G::Node;
using G::Edge;
using G::g;
using G::s;
using G::t;
int n, m, k;
inline Node *f(int i, int j) {
    if (j == 0)
        return &g[i];
    if (j == 1)
        return &g[m + i];
    if (j == 2)
        return &g[m + n + i];
    return &g[m + n + n + i];
}
int main() {
    static int i, j, c, d, x;
    scanf("%d%d%d", &n, &m, &k);
    G::n = m + n + n + k + 2;
    s = &G::g[G::n - 1], t = &G::g[G::n];
    for (i = 1; i <= m; ++i)
        new Edge(s, f(i, 0), 1);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &c, &d);
        for (j = 1; j <= c; ++j) {
            scanf("%d", &x);
            new Edge(f(x, 0), f(i, 1), 1);
        }
        new Edge(f(i, 1), f(i, 2), 1);
        for (j = 1; j <= d; ++j) {
            scanf("%d", &x);
            new Edge(f(i, 2), f(x, 3), 1);
        }
    }
    for (i = 1; i <= k; ++i)
        new Edge(f(i, 3), t, 1);

    printf("%d\n", G::dinic());
    return 0;
}
