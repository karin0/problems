#include <cstdio>
#include <queue>

typedef long long ll;
const int MAXN = 105, MAXM = 10005;
struct Edge {
    int v;
    ll w;
    Edge *next;
} se[MAXM];
Edge *adj[MAXN];
int n, m, ind[MAXN];
bool opt[MAXN];
ll k[MAXN], d[MAXN], c[MAXN];
inline void arc(int u, int v, ll w, int i) {
    Edge &e = se[i];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = se + i;
    ++ind[v];
}

int main() {
    static int i, u, v;
    static ll w, cu;
    static bool suc;
    static std::queue<int> que;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%lld%lld", c + i, k + i);
    }
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%lld", &u, &v, &w);
        arc(u, v, w, i);
    }
    for (u = 1; u <= n; ++u)
        if (ind[u] == 0)
            que.push(u), d[u] = c[u] + k[u];
    while (!que.empty()) {
        u = que.front();
        que.pop();
        cu = d[u] - k[u];
        if (cu < 0)
            d[u] = k[u], cu = 0;
        if (adj[u]) {
            for (Edge *e = adj[u]; e; e = e->next) {
                v = e->v;
                d[v] += e->w * cu;
                if (--ind[v] == 0)
                    que.push(v);
            }
        } else
            opt[u] = true;
    }
    for (u = 1; u <= n; ++u)
        if (opt[u] && d[u] > k[u])
            printf("%d %lld\n", u, d[u] - k[u]), suc = true;
    if (!suc)
        puts("NULL");

    return 0;
}
