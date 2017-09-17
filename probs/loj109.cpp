#include <cstdio>

const int MAXN = 4000005, MOD = 998244353;

int n, fa[MAXN];

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
    int m, opt, ans = 0, u, v;
    scanf("%d%d", &n, &m);
    init();
    while (m--) {
        scanf("%d%d%d", &opt, &u, &v);
        if (opt == 0)
            merge(u, v);
        else {
            ans = (ans * 2 + same(u, v)) % MOD;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}
