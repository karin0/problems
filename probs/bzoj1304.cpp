#include <cstdio>
#include <algorithm>

const int MAXN = 10005, MAXM = 5035, INF = 10007, base = 10009;
struct Edge {
    int v;
    Edge *next;
} se[MAXN << 1];
int n, m;
bool c[MAXM];
Edge *adj[MAXN];
inline void arc(int u, int v, int i) {
    se[i].v = v;
    se[i].next = adj[u];
    adj[u] = se + i;
}
// int f[MAXN][2];
int dp(int u, int fa) { // Base (n + 1)
    int v, v0, v1, vx, f0 = 1, f1 = 1;
    // int &f0 = f[u][0], &f1 = f[u][1];
    // f0 = 1;
    // f1 = 1;
    if (u <= m)
        (c[u] ? f0 : f1) = INF;
        // f[u][c[u] ^ 1] = INF;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (v == fa)
            continue;
        vx = dp(v, u);
        v1 = vx / base;
        v0 = vx % base;
        f0 += std::min(v0 - 1, v1);
        f1 += std::min(v1 - 1, v0);
    }
    return f1 * base + f0;
}

int main() {
    static int i, u, v, vx;
    scanf("%d%d", &n, &m); // 1 - m 的点是叶子
    for (i = 1; i <= m; ++i)
        scanf("%d", &vx), c[i] = vx == 1;
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        arc(u, v, i);
        arc(v, u, n + i - 1);
    }
    vx = dp(n, -1);
    printf("%d\n", std::min(vx / base, vx % base));
    return 0;
}
