#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#define INF 0x3f3f3f3f
#define MAXN 3010
#define MAXM 8010
using std::min;
using std::max;

int ans;
int n;
int adj[MAXN], cost[MAXN];
int to[MAXM], next[MAXM];
void add_edge(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}
std::stack<int> sta;
bool in_sta[MAXN];
int dfn[MAXN], low[MAXN], time;

int belong[MAXN], scc_cnt, scc_ecnt; 
int sadj[MAXN], scost[MAXN], sminid[MAXN];
bool sind[MAXN];
int sto[MAXM], snext[MAXM];
void tarjan(int u) {
    dfn[u] = ++time;
    low[u] = time;
    sta.push(u);
    in_sta[u] = true;
    int v;
    for (int e = adj[u]; e; e = next[e]) {
        v = to[e]; // Opt?
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_sta[v]) {
            low[u] = min(low[u], dfn[v]); // change?
        }
    }
    if (low[u] == dfn[u]) {
        ++scc_cnt;
        do {
            v = sta.top();
            sta.pop();
            in_sta[v] = false;
            belong[v] = scc_cnt;
            scost[scc_cnt] = min(scost[scc_cnt], cost[v]);
            sminid[scc_cnt] = sminid[scc_cnt] ? min(v, sminid[scc_cnt]) : v;
        } while (u != v); // Change?
    }
}
inline void scc_add_edge(int u, int v, int e) {
    sto[e] = v;
    snext[e] = sadj[u];
    sadj[u] = e;
}
void scc_build() {
    for (int u = 1, v; u <= n; ++u) {
        for (int e = adj[u]; e; e = next[e]) {
            v = to[e]; // Opt?
            if (belong[u] != belong[v]) {
                scc_add_edge(belong[u], belong[v], ++scc_ecnt);
                sind[belong[v]] = true;
            }
        }
    }
}
void scc_dfs(int u) {
    ans = min(ans, sminid[u]);
    for (int e = sadj[u], v; e; e = snext[e]) {
        v = sto[e];
        if (scost[v] == INF) scc_dfs(v);
    }
}

int main() {
    int u, v, e, val, p, m;
    bool fail = false;
    memset(cost, 0x3f, sizeof(cost));
    memset(scost, 0x3f, sizeof(scost));
    scanf("%d%d", &n, &p);
    while (p--) {
        scanf("%d%d", &u, &val);
        cost[u] = val;
    }
    scanf("%d", &m);
    for (e = 1; e <= m; ++e) {
        scanf("%d%d", &u, &v);
        add_edge(u, v, e);
    }
    for (u = 1; u <= n; ++u) if (!dfn[u])
        tarjan(u);
    scc_build();
    for (u = 1; u <= scc_cnt; ++u) {
        if (!sind[u]) {
            if (scost[u] == INF) {
                fail = true;
                break;
            } else {
                ans += scost[u];
            }
        }
    }
    if (fail) {
        ans = INF;
        for (u = 1; u <= scc_cnt; ++u) if (!sind[u] && scost[u] == INF)
            scc_dfs(u);
        printf("NO\n%d\n", ans);
    } else {
        printf("YES\n%d\n", ans);
    }
    return 0;
}
