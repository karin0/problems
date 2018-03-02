#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))

const int N = 51, inf = 0x3f3f3f3f;
inline void upd(int &x, const int v) {
    x = std::min(x, v);
}
inline int sq(const int x) {
    return x * x;
}

int n, a, b, f[N][N][N], g[N][N], w[N];
int main() {
    static int i, j, k, l, r, set[N], *end, minw, maxw;
    scanf("%d%d%d", &n, &a, &b);
    rep (i, 1, n)
        scanf("%d", &w[i]), set[i] = w[i];
    std::sort(set + 1, set + n + 1);
    end = std::unique(set + 1, set + n + 1);
    rep (i, 1, n)
        w[i] = std::lower_bound(set + 1, end, w[i]) - set;
    memset(g, 0x3f, sizeof(g));
    per (i, n, 1) {
        memset(f, 0x3f, sizeof(f));
        minw = maxw = w[i];
        f[i][minw][minw] = 0;
        g[i][i] = a;
        rep (j, i + 1, n) {
            upd(minw, w[j]);
            maxw = std::max(maxw, w[j]);
            rep (l, minw, maxw) rep(r, l, maxw) {
                int &ans = f[j][l][r];
                if (l <= w[j] && w[j] <= r)
                    upd(ans, f[j - 1][l][r]);
                if (w[j] == l) rep (k, l + 1, r)
                    upd(ans, f[j - 1][k][r]);
                if (w[j] == r) rep (k, l, r - 1)
                    upd(ans, f[j - 1][l][k]);
                rep (k, i, j - 1)
                    upd(ans, f[k][l][r] + g[k + 1][j]);
                if (ans < inf)
                    upd(g[i][j], ans + a + b * sq(set[r] - set[l]));
            }
        }
    }
    printf("%d\n", g[1][n]);

    return 0;
}
