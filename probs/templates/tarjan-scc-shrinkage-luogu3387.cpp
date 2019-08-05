#include <cstdio>
#include <algorithm>
#include <stack>

const int MAXN = 10005, MAXM = 100005, INF = 0x7f7f7f7f;
int n, m, w[MAXN];
struct Edge {
    int v;
    Edge *next;
} se[MAXM], *adj[MAXN];
void arc(int u, int v, int i) {
    Edge &e = se[i];
    e.v = v;
    e.next = adj[u];
    adj[u] = &e;
}

int scnt, sw[MAXN], bel[MAXN];
int dfn[MAXN], low[MAXN], tim;
void tarjan(int u) {
    static std::stack<int> sta;
    static bool ins[MAXN];
    dfn[u] = ++tim;
    low[u] = tim;
    sta.push(u);
    ins[u] = true;
    int v;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (!dfn[v])
            tarjan(v), low[u] = std::min(low[u], low[v]);
        else if (ins[v])
            low[u] = std::min(low[u], low[v]);
    }
    if (low[u] == dfn[u]) {
        ++scnt;
        do {
            v = sta.top();
            sta.pop();
            ins[v] = false;
            bel[v] = scnt;
            sw[scnt] += w[v];
        } while (u != v);
    }
}
Edge sse[MAXM], *sadj[MAXN];
int secnt;
void sarc(int u, int v) {
    Edge &e = sse[++secnt];
    e.v = v;
    e.next = sadj[u];
    sadj[u] = &e;
}
int solve() {
    static int i, u, v, que[MAXN << 1], hd, tl, sind[MAXN], f[MAXN], ans;
    for (i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i); // ***** Process all the connected parts
    for (u = 1; u <= n; ++u)
        for (Edge *e = adj[u]; e; e = e->next) // adj[i] ? 上下文
            if (bel[u] != bel[e->v])
                sarc(bel[u], bel[e->v]), ++sind[bel[e->v]]; // printf("%d to %d\n", bel[u], bel[]); // *** Use bel[u] instead of u
    hd = 1, tl = 0;
    ans = -INF;
    for (i = 1; i <= scnt; ++i) {
        f[i] = sw[i];
        ans = std::max(ans, f[i]); // ****
        if (sind[i] == 0)
            que[++tl] = i; // printf("%d inq %d\n", i, sw[i]);
    }
    while (tl - hd + 1 > 0) {
        u = que[hd++];
        for (Edge *e = sadj[u]; e; e = e->next) {
            v = e->v;
            f[v] = std::max(f[v], f[u] + sw[v]);
            ans = std::max(ans, f[v]);
            --sind[v];
            if (sind[v] == 0)
                que[++tl] = v;
        }
    }
    return ans;
}

int main() {
    static int i, u, v;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", w + i);
    for (i = 1; i <= m; ++i)
        scanf("%d%d", &u, &v), arc(u, v, i);
    printf("%d\n", solve());

    return 0;
}
