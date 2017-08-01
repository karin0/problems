#include <cstdio>
#include <vector>

const int MAXN = 1e5 + 50;

int n, chj[MAXN], to[MAXN], cost[MAXN], next[MAXN], size[MAXN];
long long weight[MAXN];
struct Edge {
    int to, cost;
    Edge(int to, int cost): to(to), cost(cost) {}
};
std::vector<Edge> chj[MAXN];
void add_edge(int f, int u, int c) {
    chj[f].push_back(Edge(u, c));
}
void dfs(int u) {
    size[u] = 1;
    int v;
    for (Edge *e = &chj[u].front(); e <= &chj[u].back(); ++e)
        if (!size[v = e -> to]) {
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
    for (u = 1; u <= n; ++u) {

        ans += cost[u] * (weight[u] = size[to[u]] * (n - size[to[u]]));
    }
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
