#include <cstdio>
#include <climits>
#include <cctype>
#include <algorithm>
#include <queue>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

const int N = 103, INF = INT_MAX;
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
        Edge() {}
        Edge (Node *_u, Node *_v, int _c) : v(_v), cap(_c), flow(0), e(_u->e) {
            _u->e = this;
        }
        /*
        void *operator new (size_t) {
            struct Edge pool[N * N * 4], *curr = pool;
            return curr++;
        }*/
    };
    void arc(Node *u, Node *v, const int c, const int rc = 0) {
        Edge *e1 = new Edge(u, v, c);
        Edge *e2 = new Edge(v, u, rc);
        e1->rev = e2;
        e2->rev = e1;
    }
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
        if (u == t)
            return lim;
        int f;
        for (Edge *&e = u->cur; e; e = e->e)
            if (e->cap > e->flow && e->v->lvl == u->lvl + 1 && (f = dfs(e->v, std::min(lim, e->cap - e->flow)))) {
                e->flow += f;
                e->rev->flow -= f;
                return f;
            }
        return 0;
    }
    int dinic() {
        int res = 0, f;
        while (bfs())
            while ((f = dfs(s, INF)) > 0)
                res += f;
        return res;
    }
}
using G::Node;
using G::Edge;
using G::g;
using G::s;
using G::t;
using G::arc;
int n, m, ans;
inline Node *f(const int i, const int j) {
    return &g[(i - 1) * m + j];
}
inline bool ok(const int i, const int j) {
    return 1 <= i && i <= n && 1 <= j && j <= m;
}
inline void try_add(const int i1, const int j1, const int i2, const int j2, const int w) {
    if (ok(i2, j2)) {
        arc(f(i1, j1), f(i2, j2), w, w);
        ans += w;
    }
}
int main() {
    static int i, j, x;
    scanf("%d%d", &n, &m);
    G::n = n * m + 2;
    s = &g[G::n];
    t = &g[G::n - 1];
    rep (i, 1, n) rep (j, 1, m) {
        scanf("%d", &x);
        ans += x;
        if ((i + j) & 1)
            arc(f(i, j), t, x);
        else
            arc(s, f(i, j), x);
    }
    rep (i, 1, n) rep (j, 1, m) {
        scanf("%d", &x);
        ans += x;
        if ((i + j) & 1)
            arc(s, f(i, j), x);
        else
            arc(f(i, j), t, x);
    }
    rep (i, 1, n) rep (j, 1, m) {
        scanf("%d", &x);
        try_add(i, j, i - 1, j, x);
        try_add(i, j, i + 1, j, x);
        try_add(i, j, i, j - 1, x);
        try_add(i, j, i, j + 1, x);
    }
    printf("%d\n", ans - G::dinic());
    return 0;
}
