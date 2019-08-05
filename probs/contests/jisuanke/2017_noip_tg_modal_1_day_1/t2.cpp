#include <cstdio>

const int MAXN = 1e5 + 50;

int n, chj[MAXN], to[MAXN], cost[MAXN], next[MAXN], size[MAXN];
long long weight[MAXN];
void add_edge(int f, int u, int c, int e) {
    to[e] = u;
    cost[e] = c;
    next[e] = chj[f];
    chj[f] = e;
}
void dfs(int u) {
    size[u] = 1;
    int v;
    for (int e = chj[u]; e; e = next[e])
        if (!size[v = to[e]]) {
            dfs(v);
            size[u] += size[v];
        }
}

int main() {
    int q, u, x, y;
    long long ans = 0;
    scanf("%d", &n);
    for (u = 2; u <= n; ++u) {
        scanf("%d%d", &x, &y);
        add_edge(x, u, y, u - 1);
    }
    dfs(1);
    for (u = 1; u <= n - 1; ++u)
        ans += cost[u] * (weight[u] = size[to[u]] * (n - size[to[u]]));
    printf("%lld\n", ans);
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d", &x, &y);
        ans += (y - cost[x - 1]) * weight[x - 1];
        cost[x - 1] = y; // Nearly forgot this..
        printf("%lld\n", ans);
    }
    return 0;
}
