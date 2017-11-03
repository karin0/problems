#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int MAXN = 55, MAXM = 1005, MAXK = 55;
int n, m, k;
struct Edge {
    int v, w;
    Edge *next;
} se[MAXM << 1];
Edge *adj[MAXN];
inline void arc(int u, int v, int w, int i) {
    Edge &e = se[i];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = se + i;
}
struct Dijk {
    int u, l, d;
    Dijk(int _u, int _l, int _d): u(_u), l(_l), d(_d) {}
};
inline bool operator < (const Dijk &a, const Dijk &b) {
    return a.d > b.d;
}
int dijkstra(int s, int t) {
    static std::priority_queue<Dijk> pque;
    static int d[MAXN][MAXK], u, v, l, res;
    static Dijk ud = Dijk(0, 0, 0);
    memset(d, 0x3f, sizeof(d));
    d[s][k] = 0;
    pque.push(Dijk(s, k, 0));
    while (!pque.empty()) {
        ud = pque.top();
        pque.pop();
        u = ud.u;
        l = ud.l;
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            if (d[v][l] > d[u][l] + e->w)
                d[v][l] = d[u][l] + e->w, pque.push((Dijk){v, l, d[v][l]});
            if (l > 0 && d[v][l - 1] > d[u][l] + (e->w >> 1))
                d[v][l - 1] = d[u][l] + (e->w >> 1), pque.push(Dijk(v, l - 1, d[v][l - 1]));
        }
    }
    res = d[t][k];
    for (l = 0; l < k; ++l)
        res = std::min(res, d[t][l]);
    return res;
}

int main() {
    static int i, u, v, w;
    scanf("%d%d%d", &n, &m, &k);
    for (i = 1; i <= m; ++i)
        scanf("%d%d%d", &u, &v, &w), arc(u, v, w, i), arc(v, u, w, m + i);
    
    printf("%d\n", dijkstra(1, n));
    return 0;
}
