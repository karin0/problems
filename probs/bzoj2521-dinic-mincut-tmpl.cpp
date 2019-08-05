#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>

const int N = 503, M = 803;
int n;
struct Node {
    struct Edge *e, *cur;
    int lvl;
} g[N], *s, *t;
struct Edge {
    Node *v;
    int flow, cap;
    Edge *next, *rev;
    Edge (Node *_u, Node *_v, int _cap, Edge *_r = NULL) : v(_v), flow(0), cap(_cap), next(_u->e), rev(_r ? _r : new Edge(_v, _u, 0, this)) {
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
        for (Edge *e = u->e; e; e = e->next)
            if (e->flow < e->cap && (v = e->v)->lvl == 0) {
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
    for (Edge *&e = u->cur; e; e = e->next)
        if (e->flow < e->cap && e->v->lvl == u->lvl + 1 && (f = dfs(e->v, std::min(lim, e->cap - e->flow))) > 0) {
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
    static int res;
    for (res = 0; bfs(); res += dfs(s, INT_MAX));
    return res;
}
int main() {
    static struct Triple {
        int u, v, w;
    } es[M];
    static int m, q, i, x;
    scanf("%d%d%d", &n, &m, &q);
    for (i = 1; i <= m; ++i)
        scanf("%d%d%d", &es[i].u, &es[i].v, &es[i].w);
    s = g + es[q].u, t = g + es[q].v;
    x = es[q].w + 1;
    for (i = 1; i <= m; ++i)
        if (i != q)
            new Edge(g + es[i].u, g + es[i].v, x - es[i].w),
            new Edge(g + es[i].v, g + es[i].u, x - es[i].w);
    printf("%d\n", dinic());

    return 0;
}
