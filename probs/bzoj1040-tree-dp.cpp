#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXV = 1000005;
typedef long long ll;

int n, val[MAXV];
struct Edge {
    int v;
    Edge *next;
    bool cut;
} se[MAXV * 2];
Edge *adj[MAXV];
void arc(int u, int v, int i) {
    se[i].v = v;
    se[i].next = adj[u];
    se[i].cut = false;
    adj[u] = se + i;
}
bool vis[MAXV];
int k1, k2, ke;
void dfs(int u, int prev) {
    int v;
    vis[u] = true;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (v == prev)
            continue;
        if (vis[v]) {
            if (!ke) {
                ke = e - se;
                e->cut = true;
                se[ke ^ 1].cut = true;
                k1 = u;
                k2 = v;
            }
        } else 
            dfs(v, u);
    }
}
ll f[MAXV][2]; // ***
void dp(int u, int prev) {
    int v;
    f[u][0] = 0;
    f[u][1] = val[u]; // get init
    for (Edge *e = adj[u]; e; e = e->next) {
        if (e->cut)
            continue;
        v = e->v;
        if (v == prev)
            continue;
        dp(v, u);
        f[u][0] += std::max(f[v][0], f[v][1]);
        f[u][1] += f[v][0];
    }
}

int main() {
    static int i, v;
    static ll ans, res;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", val + i, &v);
        arc(i, v, 2 * i);
        arc(v, i, 2 * i + 1);
    }
    for (i = 1; i <= n; ++i) {
        if (!vis[i]) { // a new tree
            dfs(i, 0);
            dp(k1, 0);
            res = f[k1][0];
            dp(k2, 0);
            ans += std::max(res, f[k2][0]);
            se[ke].cut = false;
            se[ke ^ 1].cut = false;
            ke = 0; // ***
        }
    }
    printf("%lld\n", ans);

    return 0;
}
