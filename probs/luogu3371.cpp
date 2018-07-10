#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#define MAXN 10010
#define MAXM 500010
#define INF 0x3f3f3f3f

int n, m;
int adj[MAXN], to[MAXM], cost[MAXM], next[MAXM];
void add_edge(int u, int v, int w, int e) {
    to[e] = v;
    cost[e] = w;
    next[e] = adj[u];
    adj[u] = e;
}

struct Pair {
    int u, d;
    Pair(int a, int b) {
        u = a;
        d = b;
    }
};
bool operator > (const Pair& a, const Pair& b) {
    return a.d > b.d;
}
std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair> > heap;
int d[MAXN];
void dijkstra(int s) {
    memset(d, 0x3f, sizeof(int) * (n + 3));
    d[s] = 0;
    heap.push(Pair(s, 0));
    register int u, e;
    while (!heap.empty()) {
        u = heap.top().u;
        heap.pop();
        for (e = adj[u]; e; e = next[e])
            if (d[to[e]] > d[u] + cost[e]) {
                d[to[e]] = d[u] + cost[e];
                heap.push(Pair(to[e], d[to[e]]));
            }
    }
}
int main() {
    int u, v, w, e;
    int s;
    scanf("%d%d%d", &n, &m, &s);
    for (e = 1; e <= m; ++e) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w, e);
    }
    dijkstra(s);
    for (u = 1; u <= n; ++u)
        printf("%d ", d[u] == INF ? 2147483647 : d[u]);
    return 0;
}
