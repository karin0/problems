#include <cstdio>

const int MAXN = 1005, MAXM = 205;
const int MOD = 1000000007;
int n, m, p;
char a[MAXN], b[MAXM];
/*
int solve() {
    static int i, j, k, f[MAXN][MAXM][MAXM], g[MAXN][MAXM][MAXM];
    f[0][0][0] = 1;
    g[0][0][0] = 1;
    for (i = 1; i <= n; ++i) {
        f[i][0][0] = 1;
        g[i][0][0] = 1;
        for (j = 1; j <= m; ++j) {
            for (k = 1; k <= p; ++k) {
                if (a[i] == b[j])
                    f[i][j][k] = (f[i - 1][j - 1][k] + g[i - 1][j - 1][k - 1]) % MOD;
                g[i][j][k] = (g[i - 1][j][k] + f[i][j][k]) % MOD;
            }
        }
    }
    return g[n][m][p];
}*/
int solve() {
    static int i, j, k, ii, f[2][MAXM][MAXM], g[2][MAXM][MAXM];
    f[0][0][0] = 1;
    g[0][0][0] = 1;
    for (i = 1; i <= n; ++i) {
        ii = i & 1;
        f[ii][0][0] = 1;
        g[ii][0][0] = 1;
        for (j = 1; j <= m; ++j) {
            for (k = 1; k <= p; ++k) {
                if (a[i] == b[j])
                    f[ii][j][k] = (f[ii ^ 1][j - 1][k] + g[ii ^ 1][j - 1][k - 1]) % MOD;
                else
                    f[ii][j][k] = 0; /// ***

                g[ii][j][k] = (g[ii ^ 1][j][k] + f[ii][j][k]) % MOD;
            }
        }
    }
    return g[n & 1][m][p];
}

int main() {
    scanf("%d%d%d", &n, &m, &p);
    scanf("%s%s", a + 1, b + 1);
    printf("%d\n", solve());
 
    return 0;
}
