#include <cstdio>
#include <math.h>
#include <algorithm>

const int MAXN = 200005, MAXM = 400005;
int n, mj;
struct Edge {
    int v;
    Edge *next;
} se[MAXM], *adj[MAXN];
inline void arc(int u, int v, int i) {
    Edge &e = se[i];
    e.v = v;
    e.next = adj[u];
    adj[u] = se + i;
}
int depth[MAXN], jmp[MAXN][19], tim[MAXN][19], ben[MAXN], sen[MAXN], rt;
void dfs(int u, int dep) {
    depth[u] = dep;
    ben[u] = 0;
    sen[u] = 0;
    int v, l;
    for (Edge *e = adj[u]; e; e = e->next) {
        v = e->v;
        if (!depth[v]) {
            jmp[v][0] = u;
            dfs(v, dep + 1);
            l = ben[v] + 1;
            if (l >= ben[u])
                sen[u] = ben[u], ben[u] = l;
            else if (l > sen[u])
                sen[u] = l;
        }
    }
}
int lca(int u, int v) {
    static int j;
    if (u == v)
        return u;
    if (depth[u] < depth[v])
        std::swap(u, v);
    for (j = mj; j >= 0; --j)
        if (depth[jmp[u][j]] >= depth[v])
            u = jmp[u][j];
    if (u == v)
        return u;
    for (j = mj; j >= 0; --j)
        if (jmp[u][j] != jmp[v][j])
            u = jmp[u][j], v = jmp[v][j];
    return jmp[u][0];
}
void init() {
    static int i, j;
    dfs(1, 1);
    mj = ceil(log2(ben[1]));
    for (i = 2; i <= n; ++i) {
        if (ben[jmp[i][0]] == ben[i] + 1)
            tim[i][0] = sen[jmp[i][0]] + 1;
        else
            tim[i][0] = ben[jmp[i][0]] + 1;
    }
    for (j = 1; j <= mj; ++j ) {
        for (i = 1; i <= n; ++i)
            jmp[i][j] = jmp[jmp[i][j - 1]][j - 1];
        for (i = 2; i <= n; ++i)
            tim[i][j] = std::max(tim[i][j - 1], (1 << (j - 1)) + tim[jmp[i][j - 1]][j - 1]);
    }
    /*
    for (j = 0; j <= mj; ++j ) {
        for (i = 1; i <= n; ++i)
            printf("jmp[%d][%d] = %d, tim[%d][%d] = %d\n", i, j, jmp[i][j], i, j, tim[i][j]);
    }*/
}
int up(int u, int k) {
    static int j, x;
    if (k < 0)
        return 0;
    for (j = 0; j <= mj; ++j) {
        x = k >> j;
        if (x & 1) {
            u = jmp[u][j];
            if (u <= 0)
                return 0;
        } else if (x == 0)
            break;
    }
    return u;
}/*
int kth(int u, int k) {
    static int l, lrd;
    l = lca(u, rt);
    lrd = depth[u] - depth[l]; // l is () th
    if (lrd == k)
        return l;
    else if (lrd > k)
        return up(u, k);
    else
        return up(rt, depth[rt] - depth[l] + lrd - k);
}*/

int query(int u, int k) {
    static int j, ub, res, d;
    res = 0;
    d = 0;
    ub = std::max(0, depth[u] - k);
    for (j = mj; j >= 0; --j)
        if (depth[jmp[u][j]] >= ub) {
            res = std::max(res, d + tim[u][j]);
            u = jmp[u][j];
            d += 1 << j;
        }
    res = std::max(res, d + tim[u][0]);
    return res;
}/*
int query(int u, int k) {
    static int ub, res, d;
    res = 0;
    d = 0;
    ub = std::min(1, depth[u] - k);
    while (depth[u] >= ub) {
        res = std::max(res, d + tim[u][0]);
        u = jmp[u][0];
        d += 1;
    }
    return res;
}*/

int main() {
    static int i, u, v, x, m, l, lrd, res;
    static char opt[4];
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        arc(u, v, i);
        arc(v, u, n + i - 1);
    }
    rt = 1;
    init();
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        scanf("%s%d", opt, &u);
        if (opt[0] == 'C')
            rt = u;
        else {
            scanf("%d", &x);
            --x;
            res = ben[u];
            l = lca(u, rt);
            lrd = depth[u] - depth[l]; // l is () th
            /* if (lrd == x) {
                // v = l;
            }*/
            if (x >= depth[rt] - depth[l] + lrd) {
                res = std::max(res, query(u, n));
            } else if (l == u) {
                res = query(u, n);
                v = up(rt, depth[rt] - depth[u] - x);
                if (depth[rt] - depth[v] + ben[rt] == ben[v])
                    res = std::max(res, sen[v] + x);
                else
                    res = std::max(res, ben[u] + x);
            } else if (lrd <= x) {
                v = up(rt, depth[rt] - depth[l] + lrd - x);
                res = std::max(res, lrd + query(l, n));
                if (depth[rt] - depth[v] + ben[rt] == ben[v])
                    res = std::max(res, sen[v] + x);
                else
                    res = std::max(res, ben[u] + x);
            } else {
                // v = up(u, x);
                // res = std::max(res, query(u, depth[u] - depth[v]));
                res = std::max(res, query(u, x));
                // if (l > 1)
                //    res = std::max(res, lrd + 1 + query(jmp[l][0], n));
            }
            printf("%d\n", res);
        }
    }

    return 0;
}
