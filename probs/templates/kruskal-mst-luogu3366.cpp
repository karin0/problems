#include <cstdio>
#include <algorithm>

const int MAXN = 5005, MAXM = 200005, INF = 0x7f7f7f7f;
int n, m, fa[MAXN];

void init() {
    static int i;
    for (i = 1; i <= n; ++i)
        fa[i] = i;
}
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
inline void unite(int x, int y) {
    fa[find(x)] = find(y); // *** Wrong: fa[x] = find(y)
}
inline bool same(int x, int y) {
    return find(x) == find(y);
}

struct Edge {
    int u, v, w;
} se[MAXM];
inline bool cmp(const Edge &a, const Edge &b) {
    return a.w < b.w;
}
int kruskal() {
    static int i, res;
    static bool flag;
    res = 0;
    init();
    std::sort(se + 1, se + m + 1, cmp);
    for (i = 1; i <= m; ++i) {
        if (!same(se[i].u, se[i].v))
            unite(se[i].u, se[i].v), res += se[i].w;
    }
    // Checking if the graph is connected
    flag = false;
    for (i = 1; i <= n; ++i) {
        if (fa[i] == i) {
            if (flag) 
                return INF;
            else
                flag = true;
        }
    }
    return res;
}

int main() {
    static int i, ans;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i)
        scanf("%d%d%d", &se[i].u, &se[i].v, &se[i].w);
    ans = kruskal();
    if (ans >= INF)
        puts("orz");
    else
        printf("%d\n", kruskal());
    return 0;
}
