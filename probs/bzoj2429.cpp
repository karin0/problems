#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 1004, MAXM = 504;

int n;
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
int ecnt;
struct Edge {
    int u, v, w;
} se[MAXN * MAXN];
inline bool cmp(const Edge &x, const Edge &y) {
    return x.w < y.w;
}
struct Point {
    int x, y;
} sv[MAXN];
inline int norm(const Point &x, const Point &y) {
    return (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y);
}

int a[MAXM], lim;
int main() {
    int m, i, j, ans = 0;
    scanf("%d", &m);
    for (i = 1; i <= m; ++i)
        scanf("%d", a + i);
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", &sv[i].x, &sv[i].y);
        for (j = 1; j < i; ++j)
            se[++ecnt].u = i, se[ecnt].v = j, se[ecnt].w = norm(sv[i], sv[j]);
    }
    
    init();
    std::sort(se + 1, se + ecnt + 1, cmp);
    for (i = 1; i <= ecnt; ++i) {
        if (!same(se[i].u, se[i].v)) {
                merge(se[i].u, se[i].v), lim = se[i].w;
        }
    }
    for (i = 1; i <= m; ++i) {
        if (a[i] * a[i] >= lim)
            ++ans;
    }
    printf("%d\n", ans);
    return 0;
}
