#include <cstdio>
#include <cstring>
#define MAXN 105
typedef long long LL;

int n;
const LL mod = 1000000007;

struct Matrix { // n * n
    LL val[MAXN][MAXN];

    Matrix operator * (const Matrix &b) { // WTF?
        Matrix res;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                res.val[i][j] = 0;
                for (int k = 1; k <= n; ++k) {
                    res.val[i][j] += val[i][k] * b.val[k][j];
                    res.val[i][j] %= mod;
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


int main() {
    LL k; // must be LL
    Matrix a, ans;
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            scanf("%lld", &a.val[i][j]);
    mat_qpow(a, k, ans);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            printf("%lld ", ans.val[i][j]);
        printf("\n");
    }

    return 0;
}
