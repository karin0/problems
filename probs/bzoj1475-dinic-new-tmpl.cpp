#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>

const int N = 36, INF = 0x3f3f3f3f;
namespace G {
    int n;
    struct Node {
        struct Edge *e, *cur;
        int lvl;
    } g[N * N], *s, *t;
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
int n;
inline Node *f(int i, int j) {
    return &g[(i - 1) * n + j];
}
int main() {
    static int i, j, x, sum;
    scanf("%d", &n);
    G::n = n * n + 2;
    s = &G::g[n * n + 1], t = &G::g[n * n + 2];
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j) {
            scanf("%d", &x);
            sum += x;
            Node *u = f(i, j);
            if (((i + j) & 1) == 0) {
                //printf("s to (%d %d) is %d\n", i, j, x);
                new Edge(s, u, x);
                if (i < n)
                    new Edge(u, f(i + 1, j), INF);
                if (i > 1)
                    new Edge(u, f(i - 1, j), INF);
                if (j < n)
                    new Edge(u, f(i, j + 1), INF);
                if (j > 1)
                    new Edge(u, f(i, j - 1), INF);
            } else
                new Edge(u, t, x), 
                0;//printf("(%d %d) to t is %d\n", i, j, x);
        }
    printf("%d\n", sum - G::dinic());
    return 0;
}
