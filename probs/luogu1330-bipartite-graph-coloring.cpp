#include <cstdio>
#include <algorithm>
#include <queue>

const int MAXN = 10005, MAXM = 100005, INF = 0x3f3f3f3f;
int n, m, c[MAXN];
struct Edge {
    int v;
    Edge *next;
} se[MAXM << 1], *adj[MAXN];
inline void arc(int u, int v, int i) {
    Edge &e = se[i];
    se[i].v = v;
    se[i].next = adj[u];
    adj[u] = &e;
}
int bfs(int u) {
    static int cnt[3], v;
    static std::queue<int> que;
    que.push(u);
    c[u] = 1;
    cnt[1] = 1;
    cnt[2] = 0;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            if (c[v] == 0) {
                c[v] = 3 - c[u];
                ++cnt[c[v]];
                que.push(v);
            } else if (c[v] == c[u])
                return INF;
        }
    }
    return std::min(cnt[1], cnt[2]); // *** cnt is not c
}

int main() {
    static int i, u, v, ans;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i)
        scanf("%d%d", &u, &v), arc(u, v, i), arc(v, u, m + i);
    for (i = 1; i <= n; ++i)
        if (!c[i]) {
            ans += bfs(i);
            if (ans >= INF) {
                puts("Impossible");
                return 0;
            }
        }
    printf("%d\n", ans);

    return 0;
}
