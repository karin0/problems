// Pending
#include <cstdio>
#include <queue>
#include <algorithm>
#define MAXN 100010
#define MAXM 400020 // double kill;
int ans;
int n, m;
int adj[MAXN], from[MAXN], to[MAXM], next[MAXM];
void add_edge(int u, int v, int e) {
    to[e] = v;
    from[e] = u;
    next[e] = adj[u];
    adj[u] = e;

    e += m;
    to[e] = u;
    from[e] = v;
    next[e] = adj[v];
    adj[v] = e;
}
int dist[MAXN], ind[MAXN];
void bfs(int s) {
    std::queue<int> que;
    que.push(s);
    dist[s] = 1;
    register int u, v;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        for (register int e = adj[u]; e; e = next[e]) {
            v = to[e];
            if (!dist[v]) {
                dist[v] = dist[u] + 1;
                que.push(v);
            }
        }
    }
}
void cut(int e) {
    register int u = from[e], v = to[e];
    // printf("(%d, %d)\n", u, v);
    if (dist[u] == dist[v])
        return;
    else if (dist[u] == dist[v] + 1)
        e = e > m ? e - m : e + m;
    // assert dist[u] + 1 == dist[v]
    std::queue<int> que;
    que.push(e);
    register int ee;
    while (!que.empty()) {
        e = que.front();
        que.pop();
        u = from[e], v = to[e];
        --ind[v];
        if (!ind[v]) {
            // printf("Cutting (%d, %d) makes %d gone\n", u, v, v);
            ++ans;
            for (ee = adj[v]; ee; ee = next[ee]) {
                if (dist[v] == dist[to[ee]] - 1)
                    que.push(ee);
            }
        }
    }
}


int main() {
    register int q, u, v, e;
    scanf("%d%d%d", &n, &m, &q);
    for (e = 1; e <= m; ++e) {
        scanf("%d%d", &u, &v);
        add_edge(u, v, e);
    }
    bfs(1);
    for (e = 1; e <= m; ++e) {
        u = from[e];
        v = to[e];
        if (dist[u] == dist[v] - 1)
            ++ind[v];
        else if (dist[v] == dist[u] - 1)
            ++ind[u];
    }
    while (q--) {
        scanf("%d", &e);
        cut(e);
        printf("%d\n", ans);
    }
    return 0;
}
