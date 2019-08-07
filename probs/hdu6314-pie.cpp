#include <cstdio>

#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

typedef long long ll;
typedef const int cint;

cint N = 3002, mo = 998244353;

inline void add(int &x) {
    if (x >= mo)
        x -= mo;
}
inline void sub(int &x) {
    if (x < 0)
        x += mo;
}

int c[N][N], bxp[N * N], fa[N], fb[N];

inline void init(int *f, int n, int a) {
    f[a] = 1;
    rep (i, a + 1, n) {
        int &fi = f[i] = 1;
        int *ci = c[i];
        re (j, a, i)
            sub(fi = (fi - (ll)ci[j] * f[j]) % mo);
    }
    int *cn = c[n];
    rep (i, a, n)
        f[i] = (ll)f[i] * cn[i] % mo;
}

int main() {
    int n = 3000;
    rep (i, 0, n) {
        int *ci = c[i], *cc = c[i - 1];
        ci[0] = 1;
        rep (j, 1, i) {
            add(ci[j] += cc[j]);
            add(ci[j] += cc[j - 1]);
        }
    }
    n *= n;
    bxp[0] = 1;
    rep (i, 1, n)
        add(bxp[i] = bxp[i - 1] << 1);

    int m, a, b;
    while (scanf("%d%d%d%d", &n, &m, &a, &b) == 4) {
        init(fa, n, a);
        init(fb, m, b);
        int ans = 0;
        rep (i, a, n) {
            int t = 0, u = n - i, v = u * (m - b + 1);
            rep (j, b, m)
                t = (t + (ll)fb[j] * bxp[v -= u]) % mo;
            ans = (ans + (ll)t * fa[i]) % mo;
        }
        printf("%d\n", ans);
    }

    return 0;
}
