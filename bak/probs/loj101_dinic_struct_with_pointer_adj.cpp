#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int MAXN = 1000050, MAXM = 4000050;
const int INF = 2147483647; // c <= 2 ^ 31 - 1

int n, m, s, t;
struct Edge {
    int to, cap;
    Edge* rev;
    Edge(int to, int cap, Edge* rev): to(to), cap(cap), rev(rev) {}
};
std::vector<Edge*> adj[MAXN]; // |E| = 2 * m
inline void add_edge(int u, int v, int c) {
    adj[u].push_back(new Edge(v, c, new Edge(u, 0, NULL)));
    adj[v].push_back(adj[u].back() -> rev);
    adj[v].back() -> rev = adj[u].back();
}

int dist[MAXN], que[MAXN];
inline bool bfs() {
    int front = 1, back = 0; // 手动队列
    memset(dist, 0, sizeof(int) * (n + 3)); // dist 当 vis
    
    que[++back] = s;
    dist[s] = 1; // 不用特判
    
    int u, v;
    while (front <= back) {
        u = que[front++];
        for (Edge **e = &(adj[u].front()); e <= &(adj[u].back()) ; ++e)
            if (!dist[v = (*e) -> to] && (*e) -> cap > 0)  {
                dist[v] = dist[u] + 1;
                que[++back] = v;
            }
    }
    return dist[t];
}
Edge** cur[MAXN];
int dfs(int u, int a) {
    if (u == t || a == 0)
        return a;
    int res = 0, v, f;
    for (Edge **&e = cur[u]; e <= &(adj[u].back()); ++e) {
        v = (*e) -> to;
        if (dist[u] + 1 == dist[v] && (*e) -> cap > 0 && (f = dfs(v, std::min(a, (*e) -> cap))) > 0) {
            res += f;
            a -= f;
            (*e) -> cap -= f;
            (*e) -> rev -> cap += f;
            if (!a)
                break; // 及时跳出
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

void read(int &res) {
    res = 0;
    register char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        // res = res * 10 + (ch - '0');
        res = (res << 3) + (res << 1) + (ch - '0');
        ch = getchar();
    }
}

int main() {
    int u, v, c, i;
    read(n);
    read(m);
    read(s);
    read(t);
    
    for (i = 0; i < m; ++i) {
        read(u);
        read(v);
        read(c);
        add_edge(u, v, c);
    }
    printf("%d\n", dinic());
    return 0;
}
