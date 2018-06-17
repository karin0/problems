#include <cstdio>
#include <algorithm>
#include <queue>
#include <stack>

const int N = 303, INF = 0x7f7f7f7f;
int n;
struct Node {
    struct Edge *e, *cur;
    int lvl;
} g[N], *s, *t;
struct Edge {
    Node *v;
    int cap, flow;
    Edge *next, *rev;
    Edge(Node *_u, Node *_v, int _c, Edge *_r = NULL) : v(_v), cap(_c), flow(0), next(_u->e), rev(_r ? _r : new Edge(_v, _u, 0, this)) {
        _u->e = this;
    }
};
bool bfs() {
    static Node *u, *v;
    for (u = g + 1; u <= g + n; ++u)
        u->lvl = 0, u->cur = u->e;
    std::queue<Node *> q;
    s->lvl = 1;
    q.push(s);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (Edge *e = u->e; e; e = e->next)
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
    for (Edge *&e = u->cur; e; e = e->next)
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
    static int res;
    res = 0;
    while (bfs())
        res += dfs(s, INF);
    return res;
}
int main() {
    static int m, u, v, a[N], i;
    scanf("%d%d", &n, &m);
    n += 2;
    s = g + n - 1, t = g + n;
    for (i = 1; i <= n - 2; ++i) {
        scanf("%d", &a[i]); 
        a[i] ? new Edge(s, g + i, 1) : new Edge(g + i, t, 1);
    }
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        if (a[u] == 1 && a[v] == 0)
            new Edge(g + u, g + v, 1);
        else if (a[u] != a[v])
            new Edge(g + v, g + u, 1);
    }
    printf("%d\n", dinic());
    return 0;
}
