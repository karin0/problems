#include <cstdio>
const int MAXL = 510;
const int MOD = 1e9 + 7;

int n, p, m;
long long a[MAXL][MAXL], b[MAXL][MAXL];
void work() {
    // a <- n * p, b <- p * m, res <- n * m
    long long val;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            val = 0;
            for (int k = 1; k <= p; ++k) {
                val = (val + ((a[i][k] * b[k][j] + MOD) % MOD) + MOD) % MOD;
            }
            printf("%lld ", val);
        }
        printf("\n");
    }
}

int main() {
    // Matrix a, b;
    int i, j;
    scanf("%d%d%d", &n, &p, &m);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= p; ++j)
            scanf("%lld", &a[i][j]);
    for (i = 1; i <= p; ++i)
        for (j = 1; j <= m; ++j)
            scanf("%lld", &b[i][j]);
    work();
    return 0;
}
