#include <cstdio>

const int MAXN = 10005;
int n, fa[MAXN];
void init() {
    static int i;
    for (i = 1; i <= n; ++i)
        fa[i] = i;
}
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void unite(int x, int y) {
    fa[find(x)] = find(y);
}
bool same(int x, int y) {
    return find(x) == find(y);
}

int main() {
    static int i, m, opt, x, y;
    scanf("%d%d", &n, &m);
    init();
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            unite(x, y);
        else
            putchar(same(x, y) ? 'Y' : 'N'), putchar('\n');
    }

    return 0;
}
