#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long ll;
const int MAXN = 100005, MAXM = 500005;
const ll INF = 1ll << 61;
int n, m, s, t, q, ecnt;
ll r[MAXN];
struct Edge {
    int v, w;
    Edge *next;
} se[MAXM << 1], *adj[MAXN];
inline void arc(int u, int v, int w) {
    Edge &e = se[++ecnt];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = &e;
}
struct Dij {
    int u;
    ll d;
};
inline bool operator < (const Dij &a, const Dij &b) {
    return a.d > b.d;
}
ll dijkstra() {
    static std::priority_queue<Dij> pque;
    static ll d[MAXN], nd;
    static Dij o;
    static int u, v;
    for (u = 1; u <= n; ++u)
        d[u] = INF;
    d[s] = 0;
    pque.push((Dij){s, 0});
    while (!pque.empty()) {
        o = pque.top();
        pque.pop();
        u = o.u;
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            nd = d[u] + e->w;
            if (nd <= r[v] && nd < d[v]) {
                d[v] = nd;
                pque.push((Dij){v, nd});
            }
        }
    }
    return d[t];
}

int main() {
    static int i, u, v, w, g, h, l;
    static ll ret;
    scanf("%d%d%d%d%d%d", &n, &m, &s, &t, &g, &q);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &h, &l);
        if (q == 0) {
            r[i] = INF;
            continue;
        }
        r[i] = (l - h) / q;
        if (r[i] * q < l - h)
            ++r[i];
        //printf("r[%d] = %d\n" , i, r[i]);
    }
    r[t] = INF;
    for (i = 1; i <= m; ++i)
        scanf("%d%d%d", &u, &v, &w), arc(u, v, w), arc(v, u, w);
    ret = dijkstra();
    if (ret <= g)
        printf("%lld\n", ret);
    else
        puts("wtnap wa kotori no oyatsu desu!"); // wtnap はことりのおやつです！

    return 0;
}
