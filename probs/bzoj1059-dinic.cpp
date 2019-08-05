#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 205, INF = 0x7f7f7f7f;
int n, w;
struct Node {
    struct Edge *e, *cur;
    int lvl;
} g[N << 1], *s, *t;
struct Edge {
    Node *v;
    Edge *next, *rev;
    int flow, cap;
    Edge() {}
    Edge(Node *_u, Node *_v, int _c) : v(_v), next(_u->e), flow(0), cap(_c) {}
} se[N * N * 2];
int ecnt;
void arc(Node *u, Node *v, int c) {
    se[++ecnt] = Edge(u, v, c);
    u->e = se + ecnt;
    se[++ecnt] = Edge(v, u, 0);
    v->e = se + ecnt;
    u->e->rev = v->e;
    v->e->rev = u->e;
}
bool bfs() {
    for (int i = 1; i <= n; ++i)
        g[i].lvl = 0, g[i].cur = g[i].e;
    std::queue<Node *> q;
    s->lvl = 1;
    q.push(s);
    Node *u, *v;
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
    int f, res = 0;
    for (Edge *&e = u->cur; e; e = e->next)
        if (e->cap > e->flow && e->v->lvl == u->lvl + 1 && (f = dfs(e->v, std::min(lim, e->cap - e->flow))) > 0) {
            e->flow += f;
            e->rev->flow -= f;
            res += f;
            lim -= f;
            if (lim == 0)
                return res;
        }
    return res;
}
int dinic() {
    int res = 0;
    while (bfs())
        res += dfs(s, INF);
    return res;
}

int main() {
    static int qaq, x, i, j;
    scanf("%d", &qaq);
    while (qaq--) {
        scanf("%d", &w);
        n = w * 2 + 2;
        s = &g[n - 1], t = &g[n];
        for (i = 1; i <= w; ++i)
            arc(s, &g[i], 1), arc(&g[w + i], t, 1);
        for (i = 1; i <= w; ++i)
            for (j = 1; j <= w; ++j)
                if (scanf("%d", &x), x)
                    arc(&g[i], &g[w + j], INF);
        puts(dinic() == w ? "Yes" : "No");
        if (qaq) {
            ecnt = 0;
            for (i = 1; i <= n; ++i)
                g[i].e = NULL;
        }
    }

    return 0;
}
