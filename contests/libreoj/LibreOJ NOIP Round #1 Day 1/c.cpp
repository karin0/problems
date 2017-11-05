#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int MAXN = 105, MAXM = 1003;
int n, m, vol;
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
};
inline bool operator < (const Dijk &a, const Dijk &b) {
    return a.d > b.d;
}
int dijkstra(int s, int t) {
    static std::priority_queue<Dijk> pque;
    static int d[MAXN][100005], u, v, l, res;
    static Dijk ud;
    memset(d, 0x3f, sizeof(d));
    d[s][0] = 0;
    pque.push((Dijk){s, 0, 0});
    while (!pque.empty()) {
        ud = pque.top();
        pque.pop();
        u = ud.u;
        l = ud.l;
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            if (d[v][l] > d[u][l] + e->w)
                d[v][l] = d[u][l] + e->w, pque.push((Dijk){v, l, d[v][l]});
            if (l > 0 && d[v][l + e->w] > d[u][l])
                d[v][l - 1] = d[u][l], pque.push((Dijk){v, l - 1, d[v][l - 1]});
        }
    }
    res = d[t][k];
    for (l = 0; l < k; ++l)
        res = std::min(res, d[t][l]);
    return res;
}
int solve(int s, int q, int w) {

    return 0;
}

int main() {
    static int i, u, v, w, s, kss, q;
    scanf("%d%d%d%d", &n, &m, &vol, &kss);
    for (i = 1; i <= n; ++i)
        scanf("%d %d", p + i, c + i);
    for (i = 1; i <= m; ++i)
        scanf("%d%d%d", &u, &v, &w), arc(u, v, w, i);
    for (i = 1; i <= kss; ++i)
        scanf("%d%d%d", &s, &q, &w), printf("%d\n", solve(s, q, w));
    return 0;
}
