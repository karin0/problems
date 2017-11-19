#include <cstdio>
#include <algorithm>

const int MAXN = 10005, MAXM = 20005, MAXC = 30000;
struct Edge {
    int u, v, w1, w2;
} se[MAXM];
int n, m, k;

int fa[MAXN];
inline void init() {
    for (int i = 1; i <= n; ++i)
        fa[i] = i;
}
inline int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void merge(int x, int y) {
    fa[find(x)] = find(y);
}
inline bool same(int x, int y) {
    return find(x) == find(y);
}

inline bool check(int x) {
    init();
    static int i, ccnt, kcnt, res;
    ccnt = n, kcnt = 0, res = 0;
    for (i = 1; i <= m; ++i) {
        const Edge &e = se[i];
        if (!same(e.u, e.v))
            if (e.w1 <= x)
                merge(e.u, e.v), --ccnt, ++kcnt;
    }
    if (kcnt < k)
        return false;
    else if (ccnt == 1)
        return true;
    for (i = 1; i <= m; ++i) {
        const Edge &e = se[i];
        if (!same(e.u, e.v))
            if (e.w2 <= x)
                merge(e.u, e.v), --ccnt;
    }
    return ccnt == 1;
}

int main() {
    int i, l, r, x;
    scanf("%d%d%d", &n, &k, &m);
    --m;
    for (i = 1; i <= m; ++i)
        scanf("%d%d%d%d", &se[i].u, &se[i].v, &se[i].w1, &se[i].w2);
    l = 0, r = MAXC; // (l, r]
    while (r - l > 1) {
        x = (l + r) >> 1;
        if (check(x))
            r = x;
        else
            l = x;
    }
    printf("%d\n", r);

    return 0;
}
