#include <cstdio>
#include <algorithm>
#include <queue>
#include <stack>

const int N = 4003, M = 60003, INF = 0x7f7f7f7f;
int n;
struct Node {
    struct Edge *e, *cur;
    int lvl;
    int dfn, low, bel;
    bool ins;
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
void tarjan(Node *u) {
    static int tim, scnt;
    static std::stack<Node *> sta;
    u->low = u->dfn = ++tim;
    u->ins = true;
    sta.push(u);
    Node *v;
    for (Edge *e = u->e; e; e = e->next)
        if (e->cap > e->flow) {
            v = e->v;
            if (!v->dfn)
                tarjan(v), u->low = std::min(u->low, v->low);
            else if (v->ins)
                u->low = std::min(u->low, v->dfn);
        }
    if (u->low == u->dfn) {
        ++scnt;
        do {
            v = sta.top();
            sta.pop();
            v->ins = false;
            v->bel = scnt;
        } while (u != v);
    }
}
void scc_init() {
    for (Node *u = g + 1; u <= g + n; ++u)
        if (!u->dfn)
            tarjan(u);
}

int main() {
    static int m, u[M], v, c, i;
    static Edge *es[M], *e;
    scanf("%d%d%d%d", &n, &m, &i, &v);
    s = g + i, t = g + v;
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u[i], &v, &c);
        es[i] = new Edge(g + u[i], g + v, c);
    }
    dinic();
    scc_init();
    for (i = 1; i <= m; ++i) {
        e = es[i];
        if (e->cap > e->flow)
            puts("0 0");
        else
            printf("%d %d\n", g[u[i]].bel != e->v->bel, g[u[i]].bel == s->bel && e->v->bel == t->bel);
    }
    return 0;
}
