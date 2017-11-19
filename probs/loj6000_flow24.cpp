#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int MAXN = 105;
const int INF = 99999;

int n, m, s, t;
struct Edge {
    int to, cap, rev;
    Edge(int to, int cap, int rev): to(to), cap(cap), rev(rev) {}
};
std::vector<Edge> adj[MAXN];
inline void add_edge(int u, int v, int c) {
    adj[u].push_back(Edge(v, c, adj[v].size()));
    adj[v].push_back(Edge(u, 0, adj[u].size() - 1));
}

int dist[MAXN], que[MAXN];
inline bool bfs() {
    int front = 1, back = 0;
    memset(dist, 0, sizeof(int) * (n + 3));
    
    que[++back] = s;
    dist[s] = 1;
    
    int u, v;
    while (front <= back) {
        u = que[front++];
        for (Edge *e = &(adj[u].front()); e <= &(adj[u].back()) ; ++e)
            if (!dist[v = e -> to] && e -> cap > 0)  {
                dist[v] = dist[u] + 1;
                que[++back] = v;
            }
    }
    return dist[t];
}
Edge* cur[MAXN];
int dfs(int u, int a) {
    if (u == t || a == 0)
        return a;
    int res = 0, v, f;
    for (Edge *&e = cur[u]; e <= &(adj[u].back()); ++e) {
        v = e -> to;
        if (dist[u] + 1 == dist[v] && e -> cap > 0 && (f = dfs(v, std::min(a, e -> cap))) > 0) {
            res += f;
            a -= f;
            e -> cap -= f;
            adj[v][e -> rev].cap += f;
            if (!a)
                break;
        }
    }
    return res;
}
inline int dinic() {
    int f = 0, u;
    while (bfs()) {
        for (u = 1; u <= n; ++u)
            cur[u] = &(adj[u].front());
        f += dfs(s, INF);
    }
    return f;
}

int main() {
    int u, v, i;
    scanf("%d%d", &n, &m);
    s = n + 1;
    t = n + 2;
    for (i = 1; i <= m; ++i) {
        add_edge(s, i, 1);
    }
    for (i = m + 1; i <= n; ++i) {
        add_edge(i, t, 1);
    }

    while (scanf("%d%d", &u, &v) == 2) {
        add_edge(u, v, 1);
    }
    n += 2;
    printf("%d\n", dinic());
    return 0;
}
