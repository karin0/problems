// Dinic
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define MAXN 10010
#define MAXM 200010 // double it
#define INF 2147483640
using std::min;

int n, m, s, t;
int adj[MAXN], elast = -1;
int to[MAXM], cap[MAXM], flow[MAXM], next[MAXM];
int dist[MAXN], vis[MAXN], cur[MAXN]; // why cur?
void add_edge(int u, int v, int c) {
    ++elast;
    to[elast] = v;
    cap[elast] = c; // flow = 0
    next[elast] = adj[u];
    adj[u] = elast;

    ++elast;
    to[elast] = u; // cap = flow = 0
    next[elast] = adj[v];
    adj[v] = elast;
}
bool bfs() {
    memset(vis, false, sizeof(vis));
    dist[s] = 0;
    vis[s] = true;

    std::queue<int> que;
    que.push(s);
    int v;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int e = adj[u]; e != -1; e = next[e]) {
            v = to[e];
            if (!vis[v] && cap[e] > flow[e]) {
                vis[v] = true;
                que.push(v);
                dist[v] = dist[u] + 1;
            }
        }
    }
    return vis[t]; // Can reach it?
}
int dfs(int u, int a) {  // a is the min r = (cap - flow)
    if (a == 0 || u == t) return a;
    int res = 0, f;
    // if (cur[u] == -1) cur[u] = adj[u];
    for (int &e = cur[u]; e != -1; e = next[e]) { // update cur[x]
        if (dist[u] == dist[to[e]] - 1 && (f = dfs(to[e], min(a, cap[e] - flow[e]))) > 0) {
            flow[e] += f;
            flow[e ^ 1] -= f;
            res += f;
            a -= f; // ?
            if (!a) break; // or else, another way
        }
    }
    return res;

}

int dinic() {
    int res = 0;
    while (bfs()) { // augmenting path exists
        for (int i = 1; i <= n; ++i)
            cur[i] = adj[i]; // restore the cur array
        // memset(cur, -1, sizeof(cur)); // as tag
        res += dfs(s, INF);
    }
    return res;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &s, &t);
    int tu, tv, tc;
    memset(adj, -1, sizeof(adj)); // as 0 need to be used
    for (int i = 1; i <= m; ++i) {
        scanf("%d%d%d", &tu, &tv, &tc);
        add_edge(tu, tv, tc);
    }
    //printf("goood");
    printf("%d\n", dinic());
    return 0;
}
