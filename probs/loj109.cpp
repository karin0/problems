#include <cstdio>
#include <cctype>

const int MAXN = 4000005, MOD = 998244353;

int n, fa[MAXN];

void init() {
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

void read(int &x) {
    static char ch;
    x = 0;
    ch = 0;
    while (!isdigit(ch))
        ch = getchar();
    while (isdigit(ch))
        x = x * 10 + ch - '0', ch = getchar();
}
int main() {
    int m, opt, ans = 0, u, v;
    read(n);
    read(m);
    init();
    while (m--) {
        read(opt);
        read(u);
        read(v);
        if (opt == 0)
            merge(u, v);
        else {
            ans = ((ans << 1) + same(u, v)) % MOD;
        }
    }
    
    printf("%d\n", ans);
    return 0;
}
