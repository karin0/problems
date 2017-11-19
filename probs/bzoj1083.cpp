#include <cstdio>
#include <algorithm>

const int MAXN = 305;

int n, m;

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

struct Edge {
    int u, v, w;
} se[MAXN * MAXN];
inline bool cmp(const Edge &x, const Edge &y) {
    return x.w < y.w;
}
int cnt, ans;
inline void solve() {
    int i;
    std::sort(se + 1, se + m + 1, cmp);
    for (i = 1; i <= m; ++i) {
        if (!same(se[i].u, se[i].v))
            merge(se[i].u, se[i].v), ans = std::max(ans, se[i].w), ++cnt;
    }
}

int main() {
    int i;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i)
        scanf("%d%d%d", &se[i].u, &se[i].v, &se[i].w);
    init();
    solve();

    printf("%d %d\n", cnt, ans);
    return 0;
}
