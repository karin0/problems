#include <cstdio>

const int MAXN = 105;

int n, fa[MAXN], d[MAXN]; // w[i] := s[i] - s[fa[i]]
inline void init() {
    for (int i = 0; i <= n; ++i) // ******** 0 included
        fa[i] = i, d[i] = 0;
}
inline int find(int x) {
    int f = fa[x];
    if (f == x)
        return x;
    fa[x] = find(f);
    d[x] = d[x] + d[f];
    return fa[x];
}
inline bool merge(int x, int y, int v) { // v = s[x] - s[y]
    static int fx, fy;
    fx = find(x);
    fy = find(y);
    if (fx == fy) {
        return v + d[y] == d[x]; // ***
    }
    d[fx] = v + d[y] - d[x]; // ***
    fa[fx] = fy;
    return true;
}

int main() {
    int t, qwq, m, l, r, x, i;
    bool real;
    scanf("%d", &t);
    for (qwq = 1; qwq <= t; ++qwq) {
        scanf("%d%d", &n, &m);
        init();
        real = true;
        for (i = 1; i <= m; ++i) {
            scanf("%d%d%d", &l, &r, &x);
            if (real)
                real = merge(r, l - 1, x);
        }
        puts(real ? "true" : "false");
    } 
    
    return 0;
}
