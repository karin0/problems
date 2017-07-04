// Luogu 1073
// SCC 缩点
#include <cstdio>
#include <algorithm>
#include <stack>
#define MAXN 100010
#define MAXM 1000010
using std::max;
using std::min;

int n;
int adj[MAXN];
int to[MAXM], next[MAXM];
int price[MAXN];
inline void add_edge(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}

int belong[MAXN], scc_cnt = 0;
int maxp[MAXN], minp[MAXN]; // 1 <= p <= 100, so need not to init
int sadj[MAXN];
int sto[MAXN], snext[MAXN], secnt = 0;
int scc1, sccn;

std::stack<int> sta;
bool in_sta[MAXN];
int dfn[MAXN], low[MAXN], time = 0;
void tarjan(int u) {
    dfn[u] = ++time;
    low[u] = time;
    sta.push(u);
    in_sta[u] = true;
    int v;
    for (int e = adj[u]; e; e = next[e]) {
        v = to[e];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in_sta[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u]) {
        ++scc_cnt; // make it ++ before!
        do {
            v = sta.top();
            sta.pop();
            in_sta[v] = false;
            belong[v] = scc_cnt;
            maxp[scc_cnt] = max(maxp[scc_cnt], price[v]);
            if (!minp[scc_cnt]) minp[scc_cnt] = price[v];
            else minp[scc_cnt] = min(minp[scc_cnt], price[v]);
            if (v == 1) scc1 = scc_cnt;
            if (v == n) sccn = scc_cnt; // not else if, for n could = 1
        } while (u != v);
    }

}
inline void scc_add_edge(int u, int v, int e) {
    sto[e] = v;
    snext[e] = sadj[u];
    sadj[u] = e;
}
void make_scc() {
    int v;
    for (int u = 1; u <= n; ++u) {
        for (int e = adj[u]; e; e = next[e]) {
            v = to[e];
            if (belong[u] != belong[v]) {
                scc_add_edge(belong[v], belong[u], ++secnt); // reverse it. use its belonging!!
            }
        }
    }
}

int ans = 0;
void dfs(int scc, int surmax) { // Work with an SCC
    ans = max(ans, surmax - minp[scc]);
    if (scc != scc1) {
        int v;
        static bool dfsed[MAXN];
        for (int e = sadj[scc]; e; e = snext[e]) {
            v = sto[e];
            if (!dfsed[v]) {
                dfsed[v] = true;
                dfs(v, max(surmax, maxp[v]));
            }
        }
    }
}


int main() {
    int m;
    scanf("%d%d", &n, &m); // m is fake
    int u, e;
    for (u = 1; u <= n; ++u) {
        scanf("%d", price + u);
    }
    int tu, tv, typ;
    for (e = 1; e <= m; ++e) {
        scanf("%d%d%d", &tu, &tv, &typ);
        add_edge(tu, tv, e);
        if (typ == 2) add_edge(tv, tu, m + e);
    }
    // Find SCC and suodian
    for (u = 1; u <= n; ++u) {
        if (!dfn[u]) tarjan(u);
    }
    make_scc();
    dfs(sccn, maxp[sccn]);
    printf("%d\n", ans);
    return 0;
}
