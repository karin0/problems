/*
src: luogu2044
tags:
 - 快速幂
 - 快速乘
 - 矩阵
*/
#include <cstdio>
#include <cstring>
#define MAXN 105
typedef long long LL;

LL mod;

LL qmul(LL a, LL b) { // 二进制竖式
    LL res = 0;
    for (; b; b >>= 1, (a <<= 1) %= mod)
        if (b & 1) (res += a) %= mod;
    return res;
}

struct Matrix { // n * n
    LL val[4][4];

    Matrix operator * (const Matrix &b) { // WTF?
        Matrix res;
        for (int i = 1; i <= 2; ++i) {
            for (int j = 1; j <= 2; ++j) {
                res.val[i][j] = 0;
                for (int k = 1; k <= 2; ++k) 
                    (res.val[i][j] += qmul(val[i][k], b.val[k][j])) %= mod;
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


LL k, b, a0, n, g;
int main() {
    scanf("%lld%lld%lld%lld%lld%lld", &mod, &k, &b, &a0, &n, &g);
    Matrix mat, res;
    LL ans;
    // if (mod > g) mod = g;
    mat.val[1][1] = k % mod;
    mat.val[1][2] = b % mod;
    mat.val[2][1] = 0;
    mat.val[2][2] = 1;
    mat_qpow(mat, n, res);
    ans = (qmul(res.val[1][1], a0 % mod) + res.val[1][2]) % mod;
    printf("%lld\n", ans % g);
    return 0;
}
