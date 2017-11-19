/*
f(i, a) := 第 i 年末(产仔后,死亡前) a 岁的兔子数量
f(1, 1) = 1, f(1, a) = 0 (a != 1)
f(i, a) = f(i - 1, a - 1) (1 <= a <= 10)
f(i, 0) = sum{f(i, k) | 2 <= k <= 10}
        = sum{f(i - 1, k) | 1 <= k <= 9}

g(i) = sum{f(i - 1, k - 1) | 1 <= k <= 9} + sum{f(i - 1, k - 1) | 2 <= k <= 10}
设h(i) = sum{f(i, k) | 2 <= k <= 9}
g(i) = h(i - 1) * 2 + f(i - 1, 1) + f(i - 1, 10)
*/
#include <cstdio>
#define P ((i) & 1)
typedef long long LL;
const LL MOD = 1000000007;
const int M = 11;


struct Matrix {
    LL val[13][13];

    Matrix operator * (const Matrix &b) { // WTF?
        Matrix res;
        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= M; ++j) {
                res.val[i][j] = 0;
                for (int k = 1; k <= M; ++k) {
                    res.val[i][j] = (res.val[i][j] + (val[i][k] * b.val[k][j] % MOD)) % MOD;
                }
            }
        }
        return res;
    }
};
void mat_qpow(Matrix& b, LL p, Matrix& res) {
    res = b;
    --p;
    for ( ; p; p >>= 1, b = b * b)
        if (p & 1) res = res * b;
}

int n;
int main() {
    int i, j, k;
    long long ans = 0; // Init!!
    scanf("%d", &n);
    Matrix a, res;
    for (j = 2; j <= 10; ++j)
        a.val[1][j] = 1;
    a.val[1][1] = 0;
    a.val[1][11] = 0;
    for (i = 2; i <= 11; ++i) {
        for (j = 1; j <= 11; ++j)
            a.val[i][j] = 0;
        a.val[i][i - 1] = 1;
    }
    mat_qpow(a, n - 1, res);
    for (i = 1; i <= 10; ++i) {
        for (k = 1; k <= 11; ++k) {
            ans = (ans + res.val[i][k] * (k == 2 ? 1 : 0)) % MOD;
        }
    }

    printf("%lld\n", ans);
    return 0;
}
