#include <cstdio>
#include <algorithm>
#include <queue>
#define MAXN 10010
#define MAXM 100010 // double kill;
#define INF 9999999999999999
int n, m, hp;
int adj[MAXN], to[MAXM], next[MAXM], cost[MAXN], hurt[MAXM];
void add_edge(int u, int v, int h, int e) {
    to[e] = v;
    hurt[e] = h;
    next[e] = adj[u];
    adj[u] = e;
}

long long dist[MAXN];
struct Node {
    int u;
};
inline bool operator > (Node a, Node b) {
    return dist[a.u] > dist[b.u];
}
std::priority_queue<Node, std::vector<Node>, std::greater<Node> > heap;
bool dijkstra(int max_cost) {
    std::fill(dist + 1, dist + n + 1, INF);
    dist[1] = 0;
    heap.push((Node){1});
    int u, v, e;
    while (!heap.empty()) {
        u = heap.top().u;
        heap.pop();
        for (e = adj[u]; e; e = next[e]) {
            v = to[e];
            if (cost[v] > max_cost)
                continue;
            if (dist[v] > dist[u] + hurt[e]) {
                dist[v] = dist[u] + hurt[e];
                heap.push((Node){v});
            }
        }
    }
    return dist[n] < hp;
}

inline void read(int* data) {
    *data = 0;
    char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        *data = *data * 10 + (ch - '0');
        ch = getchar();
    }
}
int main() {
    read(&n);
    read(&m);
    read(&hp);
    register int u, v, h, e, lb, ub = -1, mid;
    for (u = 1; u <= n; ++u) {
        read(cost + u);
        ub = std::max(ub, cost[u]);
    }
    lb = cost[1] - 1;
    for (e = 1; e <= m; ++e) {
        read(&u);
        read(&v);
        read(&h);
        if (u != v) {
            add_edge(u, v, h, e);
            add_edge(v, u, h, m + e);
        }
    }
    if (!dijkstra(ub)) {
        printf("AFK\n");
        return 0;
    }
    while (ub - lb > 1) { // Checking (lb, ub]
        //printf("|%d|%d|\n", lb, ub);
        mid = lb + ((ub - lb) >> 1);
        (dijkstra(mid) ? ub : lb) = mid;
    }
    printf("%d\n", ub);
    return 0;
}
