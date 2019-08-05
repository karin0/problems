#include <cstdio>
#include <vector>
#define fadj(__u) for(std::vector<int>::iterator it = g[__u].begin(); it != g[__u].end(); ++it)

const int N = 1005;
int n, nxt[N][N], deg[N];
std::vector<int> g[N];
void init(int s) {
    static int u, v, hd, tl, q[N], d[N], *nu;
    static bool vis[N];
    nu = nxt[s];
    hd = 1, tl = 0;
    q[++tl] = s;
    for (u = 1; u <= n; ++u)
        vis[u] = false;
    d[s] = 0;
    vis[s] = true;
    while (tl - hd + 1 > 0) {
        u = q[hd++];
        fadj (u) if (!vis[v = *it]) {
            d[v] = d[u] + 1;
            vis[v] = true;
            q[++tl] = v;
        }
    }
    for (u = 1; u <= n; ++u) {
        hd = 0;
        fadj (u) {
            v = *it;
            if (!hd || d[v] < d[hd] || (d[v] == d[hd] && v < hd))
                hd = v;
        }
        nu[u] = hd;
    }
}
int next(int s, int t) {
    static bool inited[N];
    if (!inited[t])
        init(t), inited[t] = true;
    return nxt[t][s];
}
double f[N][N];
double dp(int s, int t) {
    static bool calced[N][N];
    double &ans = f[s][t];
    if (calced[s][t])
        return ans;
    calced[s][t] = true;
    if (s == t)
        return ans = 0;
    int p = next(s, t); // no static!
    if (p == t)
        return ans = 1;
    p = next(p, t);
    if (p == t)
        return ans = 1;
    ans = dp(p, t);
    // printf("%d(p) to %d(t) : %lf\n", p, t, ans);
    fadj (t)
        ans += dp(p, *it); // printf("%d(p) to %d(v) , %lf\n", p,*it,ans);
    return ans = 1 + ans / deg[t];
}
int main() {
    static int m, s, t, u, v, i;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (i = 1; i <= n; ++i)
        deg[i] = 1;
    while (m--) {
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
        ++deg[u], ++deg[v];
    }
    printf("%.3lf\n", dp(s, t));

    return 0;
}
