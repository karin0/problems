#include <cstdio>
#include <algorithm>

typedef long long ll;
const int MAXN = 305;
const ll INF = 99999999999999;

int n, ne;
ll a[MAXN][MAXN], ans;
bool used[MAXN];
struct Path {
    int u, v;
    ll w;
} sp[MAXN * MAXN];
inline bool cmp(const Path &x, const Path &y) {
    return x.w < y.w;
}
inline void add_path(int u, int v, int w) {
    sp[++ne].u = u;
    sp[ne].v = v;
    sp[ne].w = w;
}

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


int main() {
    int i, j, k;
    ll d;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= n; ++j) {
            scanf("%lld", &a[i][j]);
            if (i < j)
                add_path(i, j, a[i][j]);
        }
    }
    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            d = INF;
            for (k = 1; k <= n; ++k) {
                d = std::min(d, a[i][k] + a[k][j]);
                if (d < a[i][j]) {
                    puts("-1\n");
                    return 0;
                }
            }
            if (d != a[i][j]) {
                puts("-1\n");
                return 0;
            }
        }
    }
    for (i = 1; i <= n; ++i) {
        for (j = i + 1; j <= n; ++j) {
            if (used[i] && used[j])
                continue;
            ans += a[i][j];
            for (k = 1; k <= n; ++k) {
                if (a[i][k] + a[k][j] == a[i][j]) {
                    used[k] = true;
                }
            }
        }
    }
    /*
    std::sort(sp + 1, sp + ne + 1, cmp);
    init();
    for (i = 1; i <= ne; ++i) {
        if (!same(sp[i].u, sp[i].v))
            ans += sp[i].w, merge(sp[i].u, sp[i].v), printf("Add %d/%d\n", i, ne);
    }*/
    
    printf("%lld\n", ans);
    return 0;
}
