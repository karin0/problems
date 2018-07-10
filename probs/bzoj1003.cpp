#include <cstdio>
#include <algorithm>
#include <queue>

const int MAXN = 103, MAXV = 23, INF = 0x3f3f3f3f;
int n, m, cv, ce, k;
struct Edge {
    int v, w;
    Edge *next;
} se[MAXN * MAXN];
Edge *adj[MAXV];
inline void arc(int u, int v, int w, int i) {
    Edge &e = se[i];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = se + i;
}
int d[MAXV], c[MAXN][7];
struct Cmp {
    bool operator () (int u, int v) {
        return d[u] < d[v];
    }
};
int dijkstra(int l, int r) {
    static int u, clos, v;
    clos = 0;
    for (u = l; u <= r; ++u)
        clos |= closed[u];
    for (u = 1; u <= cv; ++u)
        d[u] = INF;
    d[1] = 0;
    std::priority_queue<int, std::vector<int>, Cmp> pque;
    pque.push(1);
    while (!pque.empty()) {
        u = pque.top();
        pque.pop();
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            if ((clos >> v) & 1)
                continue;
            if (d[u] + e->w < d[v])
                d[v] = d[u] + e->w, pque.push(v);
        }
    }
    return (d[cv] < INF) ? d[cv] * (r - l + 1) : d[cv];
}

int main() {
    static int i, j, u, v, w, dc, f[MAXN];
    scanf("%d%d%d%d", &n, &cv, &k, &ce);
    for (i = 1; i <= ce; ++i)
        scanf("%d%d%d", &u, &v, &w), arc(u, v, w, i), arc(v, u, w, ce + i);
    scanf("%d", &dc);
    for (i = 1; i <= dc; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        for (j = v; j <= w; ++j)
            closed[j] |= 1 << u;
    }
    for (i = 1; i <= n; ++i) {
        f[i] = dijkstra(1, i);
        for (j = 1; j < i; ++j)
            f[i] = std::min(f[i], f[j] + dijkstra(j + 1, i) + k);
    }
    printf("%d\n", f[n]);

    return 0;
}
