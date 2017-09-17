#include <cstdio>

const int MAXN = 20, MAXM = 105;

int n, m;
long long f[MAXN][MAXM];

int main() {
    int i, j;
    scanf("%d%d", &m, &n);
    
    for (j = 1; j <= m; ++j)
        f[0][j] = 2;
    
    f[0][0] = 1; // **
    for (i = 1; i <= n; ++i) {
        f[i][0] = 1;
        for (j = 1; j <= m; ++j)
            f[i][j] = f[i - 1][j - 1] + f[i][j - 1];
    }
    
    printf("%lld\n", f[n][m]);
    return 0;
}
