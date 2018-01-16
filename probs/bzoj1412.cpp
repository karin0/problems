#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>

const int MAXN = 103;
struct Network {
    int n;
    struct Edge;
    struct Node {
        struct Edge *adj, *cur;
        int lvl;
    } g[MAXN * MAXN], *s, *t;
    struct Edge {
        Node *v;
        int flow, cap;
        Edge *next, *rev;
        Edge (Node *_u, Node *_v, int _cap) : v(_v), flow(0), cap(_cap), next(_u->adj) {}
    };
    bool bfs() {
        for (int i = 1; i <= n; ++i)
            g[i].lvl = 0, g[i].cur = g[i].adj;
        std::queue<Node *> q;
        s->lvl = 1;
        q.push(s);
        while (!q.empty()) {
            Node *u = q.front(), *v;
            q.pop();
            for (Edge *e = u->adj; e; e = e->next)
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
        for (Edge *e = u->cur; e; e = e->next)
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
        int res = 0;
        while (bfs())
            res += dfs(s, INT_MAX);
        return res;
    }
    void arc(Node *u, Node *v, int cap) {
        u->adj = new Edge(u, v, cap);
        v->adj = new Edge(v, u, 0);
        u->adj->rev = v->adj;
        v->adj->rev = u->adj;
    }
    Node *ton(int i, int j) {
        static Node *mem[MAXN][MAXN];
        if (mem[i][j])
            return mem[i][j];
        return mem[i][j] = (g + (++n));
    }

} g;
int main() {
    static int n, m, a[MAXN][MAXN], i, j, x;
    scanf("%d%d", &n, &m);
    g.s = g.ton(0, 0);
    g.t = g.ton(0, 1);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j) {
            scanf("%d", &x);
            a[i][j] = x;
            if (x == 1)
                g.arc(g.s, g.ton(i, j), INT_MAX);
            else if (x == 2)
                g.arc(g.ton(i, j), g.t, INT_MAX);
        }
    for (i = 1; i <= n; ++i)
        for (j = 1; j < m; ++j)
            if (!((a[i][j] == 1 && a[i][j + 1] == 1) || (a[i][j] == 2 && a[i][j + 1] == 2)))
                g.arc(g.ton(i, j), g.ton(i, j + 1), 1), g.arc(g.ton(i, j + 1), g.ton(i, j), 1);
    for (i = 1; i < n; ++i)
        for (j = 1; j <= m; ++j)
            if (!((a[i][j] == 1 && a[i + 1][j] == 1) || (a[i][j] == 2 && a[i + 1][j] == 2)))
                g.arc(g.ton(i, j), g.ton(i + 1, j), 1), g.arc(g.ton(i + 1, j), g.ton(i, j), 1);
    printf("%d\n", g.dinic());

    return 0;
}
