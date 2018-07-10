#include <cstdio>
#include <algorithm>

typedef long long ll;
const int MAXN = 1000005, UNUSED = 1;

int n;
struct Edge {
    int v, w;
    Edge *next;
    bool disabled;
} se[MAXN << 1];
Edge *adj[MAXN];
inline void arc(int u, int v, int w, int i) {
    //se[i] = (Edge){v, w, adj[u], false};
    Edge &e = se[i];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    e.disabled = false;
    adj[u] = se + i;
}
int fa[MAXN], fae[MAXN], ccnt, lca; // need to be reset;
struct Node {
    int u, e;
} cir[MAXN];
void dfs(int u, int prev) {
    static bool flag[MAXN];
    static int ch[MAXN];
    fa[u] = prev;
    int v;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (v == prev)
            continue;
        if (fa[v]) { // Found a circle of (u, v)
            if (lca)
                continue;
            int o;
            for (o = u; o > 0; o = fa[o])
                flag[o] = true;
            cir[++ccnt] = (Node){u, (int)(e - se)};
            for (o = v; !flag[o]; o = fa[o])
                cir[++ccnt] = (Node){o, fae[o]};
            lca = o;
            for (o = u; o != lca; o = fa[o])
                ch[fa[o]] = o;
            for (o = lca; o != u; o = ch[o])
                cir[++ccnt] = (Node){o, fae[ch[o]]};
        } else {
            fae[v] = e - se;
            dfs(v, u);
        }
    }
}
ll dia;
ll dp(int u, int prev) {
    int v;
    ll d, sv = 0, mv = 0;
    for (Edge *e = adj[u]; e; e = e->next) {
        if (e->disabled)
            continue;
        v = e->v;
        if (v == prev)
            continue;
        d = dp(v, u) + e->w;
        if (d > mv)
            sv = mv, mv = d;
        else if (d > sv)
            sv = d;
    }
    dia = std::max(dia, mv + sv);
    return mv;
}
ll val[MAXN << 1];
int ind[MAXN << 1], hd, tl, cnt; // size = (hd - tl) - 1
inline void clear() {
    hd = 1;
    tl = 0;
    cnt = 0;
}
void push(ll x) {
    while (tl >= hd && val[tl] < x)
        --tl;
    // tl = std::upper_bound(val + hd, val + tl + 1, -x) - val - 1;
    val[++tl] = x;
    ind[tl] = ++cnt;
}
ll top() { // ind >= cnt - ccnt + 2 的元素的最大值
    static int v;
    v = cnt - ccnt + 2;
    while (tl >= hd && ind[hd] < v)
        ++hd;
    // hd = std::lower_bound(ind + hd, ind + tl + 1, cnt - ccnt + 2) - ind;
    return val[hd];
}
ll solve() {
    static int u, v, i, e;
    static ll res, tmp, dep[MAXN], pre;
    res = 0;
    for (u = 1; u <= n; ++u) {
        if (!fa[u]) {
            dfs(u, -1);
            tmp = 0;
            for (i = 1; i <= ccnt; ++i) {
                e = cir[i].e;
                se[e].disabled = true;
                se[e ^ 1].disabled = true;
            }
            for (i = 1; i <= ccnt; ++i) {
                dia = 0;
                v = cir[i].u;
                dep[v] = dp(v, -1);
                tmp = std::max(tmp, dia);
            }
            clear();
            push(dep[cir[1].u]); // - pre[1];
            pre = 0;
            for (i = 2; i <= ccnt; ++i) {
                pre += se[cir[i - 1].e].w;
                tmp = std::max(tmp, top() + dep[cir[i].u] + pre);
                push(dep[cir[i].u] - pre);
            }
            pre += se[cir[ccnt].e].w;
            tmp = std::max(tmp, top() + dep[cir[1].u] + pre);
            push(dep[cir[1].u] - pre);
            for (i = 2; i <= ccnt; ++i) {
                pre += se[cir[i - 1].e].w;
                tmp = std::max(tmp, top() + dep[cir[i].u] + pre);
                push(dep[cir[i].u] - pre);
            }
            res += tmp;
            ccnt = 0;
            lca = 0;
        }
    }
    return res;
}
void read(int &x) {
    static char ch;
    ch = 0;
    x = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
}
int main() {
    static int u, v, w;
    read(n);
    for (u = 1; u <= n; ++u) {
        read(v);
        read(w);
        arc(u, v, w, u << 1);
        arc(v, u, w, (u << 1) | 1);
    }
    printf("%lld\n", solve());
    return 0;
}
