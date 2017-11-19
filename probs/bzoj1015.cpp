#include <cstdio>
#include <vector>

const int MAXM = 200005;

int n, m, res[MAXM * 2];
std::vector<int> g[MAXM * 2], del[MAXM * 2];
bool removed[MAXM * 2];

struct Edge {
    int u, v;
    bool flag;
} se[MAXM];

int fa[MAXM * 2];
inline void init() {
    for (int i = 0; i < n; ++i)
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


int main() {
    int i, k, x, y, ans = 0;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        se[i].u = x;
        se[i].v = y;
        g[x].push_back(i);
        g[y].push_back(i);
        se[i].flag = false;
    }
    scanf("%d", &k);
    for (i = 0; i < k; ++i) {
        scanf("%d", &x);
        removed[x] = true; // ***
        for (int *p = &g[x].front(); p && p <= &g[x].back(); ++p)
            if (!se[*p].flag)
                del[i].push_back(*p), se[*p].flag = true;
    }
    init();
    for (i = 0; i < m; ++i)
        if (!se[i].flag)
            merge(se[i].u, se[i].v);
    for (i = 0; i < n; ++i)
        if (fa[i] == i && (!removed[i]))
            ++ans;
    for (i = k - 1; i >= 0; --i) {
        res[i] = ans;
        ++ans; // *** 该星球被重新加入
        for (int *p = &del[i].front(); p && p <= &del[i].back(); ++p) {
            if (!same(se[*p].u, se[*p].v))
                merge(se[*p].u, se[*p].v), --ans;
        }
    }
    printf("%d\n", ans);
    for (i = 0; i < k; ++i)
        printf("%d\n", res[i]);


    return 0;
}
