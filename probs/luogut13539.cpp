#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;
const int MAXN = 1000005;
int n, m, ecnt;
ll w[MAXN << 1];
struct Edge {
    int v;
    Edge *next;
} se[MAXN << 1], *adj[MAXN << 1];
inline void arc(const int u, const int v) {
    Edge &e = se[++ecnt];
    e.v = v;
    e.next = adj[u];
    adj[u] = &e;
}
bool fail;
ll clim;
int lim;
ll dfs(const int u, ll backup) { // 返回当前子树需要借用的祖先种类的围巾的数目；backup 为祖先能提供的援助
    ll llim = (u > n + 1) ? clim : lim;
    ll res = llim - w[u];
    // printf("lim = %d: %d has received %lld\n", lim, u, backup);
    if (w[u] < llim && res > backup) {
        fail = true;
        return -1;
    }
    backup += w[u] - llim;
    ll req;
    for (Edge *e = adj[u]; e; e = e->next) {
        req = dfs(e->v, backup);
        if (fail)
            return -1;
        backup -= req;
        if (backup < 0) {
            fail = true;
            return -1;
        }
        res += req;
    }
    // printf("lim = %d: %d left %lld and used %lld\n", lim, u, backup, res);
    return std::max(res, 0ll);
}
bool vis[MAXN];
void dfs0(const int u) {
    vis[u] = true;
    for (Edge *e = adj[u]; e; e = e->next)
        dfs0(e->v);
}
int tcrt, tcsiz, ccnt, csiz[MAXN], fa[MAXN];
ll tcsw;
bool inc[MAXN];
bool pre_invest(const int u) {
    if (vis[u])
        return true;
    vis[u] = true;
    for (Edge *e = adj[u]; e; e = e->next)
        if (pre_invest(e->v))
            inc[u] = true;
    return inc[u];
}
void invest(int u) {
    if (u == tcrt && tcsiz > 0)
        return;
    tcsw += w[u];
    ++tcsiz;
    for (Edge *e = adj[u]; e; e = e->next)
        if (inc[e->v])
            invest(e->v);
        else
            arc(n + 1 + ccnt, e->v);
}
bool check(const int x) {
    static ll left;
    static int i;
    fail = false;
    lim = x;
    w[n + 1] = x;
    left = m - dfs(n + 1, m);
    if (fail)
        return false;
    for (i = 1; i <= ccnt; ++i) {
        clim = (ll)x * csiz[i];
        left -= dfs(n + 1 + i, left);
        if (fail || left < 0)
            return false;
    }
    return true;
}
inline int up(int u) {
    static bool uvis[MAXN];
    while (!uvis[u])
        uvis[u] = true, u = fa[u];
    return u;
}
inline void read(int &x) {
    char ch = getchar();
    while (ch != '-' && !isdigit(ch))
        ch = getchar();
    if (ch == '-') {
        x = -1;
        while (isdigit(getchar()));
        return;
    }
    x = 0;
    while (isdigit(ch)) {
        x = x * 10 + (ch - '0');
        ch = getchar();
    }
}
int main() {
    static int i, u, l = 0x7f7f7f7f, r, x;
    static ll sw;
    read(n);
    read(m);
    for (i = 1; i <= n; ++i) {
        read(u);
        fa[i] = u;
        if (u == -1)
            arc(n + 1, i);
        else
            arc(u, i); 
    }
    for (i = 1; i <= n; ++i)
        read(x), w[i] = x, sw += x, l = std::min(l, x);
    dfs0(n + 1);
    for (i = 1; i <= n; ++i)
        if (!vis[i]) {
            ++ccnt;
            u = up(i);
            tcrt = u;
            tcsw = 0;
            tcsiz = 0;
            pre_invest(u);
            invest(u);
            w[n + 1 + ccnt] = tcsw;
            csiz[ccnt] = tcsiz;
        }
    r = (sw + m) / n + 1;
    while (r - l > 1) {
        x = (l + r) >> 1;
        if (check(x)) // 存在方案使得最小权值不少于 x
            l = x;
        else
            r = x;
    }
    printf("%d\n", l);
    return 0;
}
