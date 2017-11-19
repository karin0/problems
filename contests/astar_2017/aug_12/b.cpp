#include <cstdio>
const int MAXN = 100010;

int fa[MAXN], rel[MAXN];
inline void init() {
    for (int i = 1; i <= MAXN; ++i)
        fa[i] = i, rel[i] = 1;
}
inline int find(int x) {
    int f = fa[x];
    if (f == x)
        return x;
    fa[x] = find(f);
    rel[x] = rel[x] == rel[f];
    return fa[x];
}
inline void merge(int x, int y, int d) {
    int fx = find(x), fy = find(y);
    fa[fx] = fy;
    rel[fx] = rel[x] ? (rel[y] == d) : (rel[y] != d);
}
inline int query(int x, int y) {
    if (find(x) != find(y))
        return -1;
    return rel[x] == rel[y];
}


int t, ans[MAXN];
int main() {
    int l, x, y, c, ret, cnt = 0;
    scanf("%d\n", &l);
    init();
    while (l--) {
        ++cnt;
        scanf("%d%d%d", &x, &y, &c);
        ret = query(x, y);
        if (ret == -1)
            merge(x, y, c);
        else if (ret != c) {
            ans[++t] = cnt;
            cnt = 0;
            init();
        }
    }
    printf("%d\n", t);
    for (int i = 1; i <= t; ++i)
        printf("%d\n", ans[i]);
    return 0;
}
