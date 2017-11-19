#include <cstdio>
#include <algorithm>

const int MAXN = 205;

int n, d[MAXN][MAXN];
double p0[MAXN], p[MAXN][MAXN];

inline void init() {
    int i, j, k, sd;
    for (k = 1; k <= n; ++k)
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= n; ++j)
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
    for (i = 1; i <= n; ++i) {
        sd = 0;
        for (j = 1; j <= n; ++j)
            sd += d[i][j];
        for (j = 1; j <= n; ++j)
            if (i != j)
                p[i][j] = (double)d[i][j] / sd;
    }
}

struct Matrix {
    double a[MAXN][MAXN];
};
Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            c.a[i][j] = 0.0;
            for (int k = 1; k <= n; ++k) {
                c.a[i][j] += a.a[i][k] * b.a[k][j];
            }
        }
    }
    return c;
}

inline void qpow(Matrix &a, int p, Matrix &res) {
    res = a;
    --p;
    for (; p; p >>= 1, a = a * a)
        if (p & 1)
            res = res * a;
}

int main() {
    int i, j, k, t;
    double v;
    Matrix a, res;
    scanf("%d%d", &n, &t);
    for (i = 1; i <= n; ++i)
        scanf("%lf", p0 + i);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            scanf("%d", &d[i][j]);
    init();
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= n; ++j)
            a.a[i][j] = p[j][i];
    qpow(a, t, res);
    for (i = 1; i <= n; ++i) {
        v = 0.0;
        for (j = 1; j <= n; ++j) {
            v += res.a[i][j] * p0[j];
        }
        printf("%.6lf\n", v);
    }

    return 0;
}
