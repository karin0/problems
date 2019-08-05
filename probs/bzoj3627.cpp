#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
 
const int MAXN = 10003, MAXM = 20003, MAXK = 11, BASE = 131, MOD = 19260817, INF = 0x3f3f3f3f;
int n, m, k, gfuel, gwait;
int id[MOD + 3], gas[53], gcnt, gecnt;
double wait[MAXN];
bool ga[MAXN], sig[MAXN];
struct Edge {
    int v;
    double w;
    Edge *next;
} se[MAXM << 1], *adj[MAXM];
struct Edge_o {
    int v, wt;
    double w;
    Edge_o *next;
} seg[55 * 55], *adjg[55];
inline void arc(int u, int v, double w, int i) {
    Edge &e = se[i];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = &e;
}
inline void arc_g(int u, int v, double w, int wt) {
    Edge_o &e = seg[++gecnt];
    e.v = v;
    e.w = w;
    e.wt = wt;
    e.next = adjg[u];
    adjg[u] = &e;
}
struct Dijk {
    int u, l;
    double d;
};
inline bool operator < (const Dijk &a, const Dijk &b) {
    return a.d > b.d;
}
double d[MAXN][MAXK];
void dijkstra(int s) {
    static int u, v, l;
    static Dijk ud;
    std::priority_queue<Dijk> pque;
    for (u = 1; u <= n; ++u)
        for (l = 0; l <= k; ++l)
            d[u][l] = INF;
    d[s][k] = 0;
    pque.push((Dijk){s, k, 0});
    while (!pque.empty()) {
        ud = pque.top();
        pque.pop();
        u = ud.u;
        l = ud.l;
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            if (sig[u]) {
                if (l > 0 && d[v][l - 1] > d[u][l] + wait[u] + e->w)
                    d[v][l - 1] = d[u][l] + wait[u] + e->w, pque.push((Dijk){v, l - 1, d[v][l - 1]});
            } else if (d[v][l] > d[u][l] + e->w)
                d[v][l] = d[u][l] + e->w, pque.push((Dijk){v, l, d[v][l]});
        }
    }
}
double dijkstra_g(int s, int t) {
    static int u, v, l, wt;
    static double res;
    static Dijk ud;
    std::priority_queue<Dijk> pque;
    for (u = 1; u <= n; ++u)
        for (l = 0; l <= k; ++l)
            d[u][l] = INF;
    d[s][k] = 0;
    pque.push((Dijk){s, k, 0});
    while (!pque.empty()) {
        ud = pque.top();
        pque.pop();
        u = ud.u;
        l = ud.l;
        for (Edge_o *e = adjg[u]; e; e = e->next) {
            v = e->v;
            wt = e->wt;
            if (l >= wt && d[v][l - wt] > d[u][l] + e->w)
                d[v][l - wt] = d[u][l] + e->w, pque.push((Dijk){v, l - wt, d[v][l - wt]});
        }
    }
    res = d[t][k];
    for (l = 0; l < k; ++l)
        res = std::min(res, d[t][l]);
    return res;
}
 
int main() {
    static int i, j, ha, tr, tg, u, v, w, len, s, t, l;
    static double ans;
    static char st[23], su[23], sv[23], *ch;
    scanf("%d%d%d%d%d", &n, &m, &k, &gfuel, &gwait);
    for (i = 1; i <= n; ++i) {
        scanf("%s%d%d", st, &tr, &tg);
        ha = 0;
        for (ch = &st[0]; *ch; ++ch)
            ha = ((ha * BASE + (int)*ch) % MOD + MOD) % MOD;
        if (id[ha])
            printf("%d is %d\n", i, id[ha]);
        id[ha] = i;
        if (tr)
            sig[i] = true, wait[i] = (double)tr * tr / (2.0 * (tr + tg));
        if (strstr(st, "gas"))
            gas[++gcnt] = i, ga[i] = true;
        else {
            len = ch - st;
            if (!s && len == 5 && strcmp(st, "start") == 0)
                s = i;
            else if (!t && len == 3 && strcmp(st, "end") == 0)
                t = i;
        }
    }
    for (i = 1; i <= m; ++i) {
        scanf("%s%s%s%d", su, sv, st, &w);
        ha = 0;
        for (ch = &su[0]; *ch; ++ch)
            ha = ((ha * BASE + (int)*ch) % MOD + MOD) % MOD;
        u = id[ha];
        ha = 0;
        for (ch = &sv[0]; *ch; ++ch)
            ha = ((ha * BASE + (int)*ch) % MOD + MOD) % MOD;
        v = id[ha];
        arc(u, v, w, i);
        arc(v, u, w, m + i);
    }
    for (i = 1; i <= gcnt; ++i) {
        u = gas[i];
        dijkstra(u);
        for (j = i + 1; j <= gcnt; ++j) {
            v = gas[j];
            for (l = 0; l <= k; ++l)
                if (d[v][l] <= gfuel) {
                    arc_g(i, j, d[v][l] + gwait, k - l);
                    arc_g(j, i, d[v][l] + gwait, k - l);
                }
        }
        for (l = 0; l <= k; ++l) {
            if (d[s][l] <= gfuel)
                arc_g(gcnt + 1, i, d[s][l], k - l);
            if (d[t][l] <= gfuel)
                arc_g(i, gcnt + 2, d[t][l] + gwait, k - l);
        }
    }
    ans = dijkstra_g(gcnt + 1, gcnt + 2);
    dijkstra(s);
    for (l = 0; l <= k; ++l)
        if (d[t][l] <= gfuel && d[t][l] < ans)
            ans = d[t][l];
    printf("%.3lf\n", ans);
 
    return 0;
}
