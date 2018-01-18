#include <cstdio>
#include <algorithm>
#include <stack>

const int N = 103, M = 503;
template <class T>
struct Edge {
    T *v;
    Edge *next;
    Edge (T *_u, T *_v) : v(_v), next(_u->e) {}
};
struct Node {
    struct Edge<Node> *e;
    int w, v, dfn, low;
    struct SCC *bel;
    bool ins;
} g[N];
struct SCC {
    struct Edge<SCC> *e;
    int w, v, f[M], in_deg;
} sg[N];
int n, m, scnt;
template <typename T>
void arc(T *u, T *v) {
    u->e = new Edge<T>(u, v);
}
void tarjan(Node *u) {
    static int tim = 0;
    static std::stack<Node *> sta;
    u->dfn = ++tim, u->low = tim;
    sta.push(u);
    u->ins = true;
    Node *v;
    for (Edge<Node> *e = u->e; e; e = e->next) {
        v = e->v;
        if (!v->dfn)
            tarjan(v), u->low = std::min(u->low, v->low);
        else if (v->ins)
            u->low = std::min(u->low, v->dfn);
    }
    if (u->low == u->dfn) {
        SCC *scc = sg + (++scnt);
        do {
            v = sta.top();
            sta.pop();
            v->ins = false;
            v->bel = scc;
            scc->v += v->v;
            scc->w += v->w;
        } while (u != v);
    }
}
void scc_init() {
    for (int i = 1; i <= n; ++i) // ***
        if (!g[i].dfn)
            tarjan(g + i);
}
void dfs(SCC *u) {
    SCC *v;
    int i, j;
    u->f[u->w] = u->v;
    for (Edge<SCC> *e = u->e; e; e = e->next) {
        v = e->v;
        dfs(v);
        for (i = m; i >= u->w; --i)
            for (j = 0; j <= i - u->w; ++j)
                u->f[i] = std::max(u->f[i], u->f[i - j] + v->f[j]); // ???
    }
}

int main() {
    // freopen("install.in", "r", stdin);
    // freopen("install.out", "w", stdout);
    static int i, d[N], ans;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", &g[i].w);
    for (i = 1; i <= n; ++i)
        scanf("%d", &g[i].v);
    for (i = 1; i <= n; ++i) {
        scanf("%d", d + i);
        if (d[i])
            arc(g + d[i], g + i);
    }
    scc_init();
    for (i = 1; i <= n; ++i)
        if (d[i] && g[d[i]].bel != g[i].bel)
            arc(g[d[i]].bel, g[i].bel), ++g[i].bel->in_deg;
    for (i = 1; i <= scnt; ++i)
        if (sg[i].in_deg == 0)
            arc(sg + 0, sg + i);
    dfs(sg + 0);
    for (i = 0; i <= m; ++i)
        ans = std::max(ans, sg[0].f[i]);
    printf("%d\n", ans);

    return 0;
}
