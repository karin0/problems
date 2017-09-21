#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 1004;

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
    double x, y;
} sv[MAXN];
inline double norm(const Point &x, const Point &y) {
    return (x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y);
}

int main() {
    int m, i, j;
    scanf("%d%d", &n, &m);

    for (i = 1; i <= n; ++i) {
        scanf("%lf%lf", &sv[i].x, &sv[i].y);
        for (j = 1; j < i; ++j)
            se[++ecnt].u = i, se[ecnt].v = j, se[ecnt].w = norm(sv[i], sv[j]);
    }
    
    init();
    std::sort(se + 1, se + ecnt + 1, cmp);
    for (i = 1; ; ++i) {
        if (!same(se[i].u, se[i].v)) {
            if (n == m) {
                printf("%.2lf\n", sqrt(se[i].w));
                return 0;
            } else
                merge(se[i].u, se[i].v), --n;
        }
    }
    return 0;
}
