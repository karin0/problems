#include <cstdio>
#include <algorithm>

typedef long long ll;
const int MAXN = 1000005;
int n;
struct Edge {
    int v, w;
    Edge *next;
} se[MAXN << 1];
Edge *adj[MAXN];
inline void arc(int u, int v, int w, int i) {
    Edge &e = se[i];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = se + i;
}
ll ans;
bool vis[MAXN];
int dfs(int u) {
    int v, res = 1, ret;
    vis[u] = true;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (!vis[v]) {
            res += (ret = dfs(v));
            ans += std::abs(n - (ret << 1)) * (ll)e->w;
        }
    }
    return res;
}
int main() {
    static int i, u, v, w;
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        arc(u, v, w, i);
        arc(v, u, w, n + i - 1);
    }
    dfs(1);
    printf("%lld\n", ans);

    return 0;
}
