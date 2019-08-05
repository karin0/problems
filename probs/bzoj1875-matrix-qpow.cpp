#include <cstdio>

typedef long long ll;
const int N = 22, M = 62, mo = 45989;
int w;
struct Matrix {
    int v[M << 1][M << 1];
    int *operator [] (const int i) {
        return v[i];
    }
    Matrix operator * (Matrix &b) const {
        static int i, j, k;
        Matrix res;
        for (i = 0; i < w; ++i)
            for (j = 0; j < w; ++j) {
                res[i][j] = 0;
                for (k = 0; k < w; ++k)
                    res[i][j] = (res[i][j] + (ll)v[i][k] * b[k][j]) % mo;
            }
        return res;
    }
};
void qpow(Matrix a, int x, Matrix &res) { // would change a
    for (res = a, --x; x; a = a * a, x >>= 1)
        if (x & 1)
            res = res * a;
}
struct Edge {
    int u, v;
} es[M << 1];
int main() {
    static int n, m, q, s, t, u, v, i, j, ans;
    static bool f[M << 1], g[M << 1];
    static Matrix c, res;
    scanf("%d%d%d%d%d", &n, &m, &q, &s, &t);
    for (i = 0; i < m; ++i) {
        scanf("%d%d", &u, &v);
        es[w].u = u, es[w++].v = v;
        es[w].u = v, es[w++].v = u;
    }
    for (i = 0; i < w; ++i) {
        for (j = 0; j < w; ++j)
            if (es[i].u == es[j].v && (i ^ j) != 1)
                c[i][j] = 1;
        f[i] = es[i].u == s;
        g[i] = es[i].v == t;
    }
    qpow(c, q - 1, res);
    for (i = 0; i < w; ++i) if (g[i])
        for (j = 0; j < w; ++j) if (f[j])
            ans = (ans + res[i][j]) % mo;
    printf("%d\n", ans);
    return 0;
}
