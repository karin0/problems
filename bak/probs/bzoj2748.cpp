#include <cstdio>

const int MAXN = 55, MAXV = 1010;

int n, w0, ub, w[MAXN];
bool f[MAXN][MAXV];

int main() {
    int i, j, ans;
    scanf("%d%d%d", &n, &w0, &ub);
    for (i = 1; i <= n; ++i)
        scanf("%d", w + i);
    
    f[0][w0] = true;
    for (i = 1; i <= n; ++i)
        for (j = 0; j <= ub; ++j)
            f[i][j] = (j - w[i] >= 0 && f[i - 1][j - w[i]]) || (j + w[i] <= ub && f[i - 1][j + w[i]]);
    ans = -1;
    for (j = ub; j >= 0; --j)
        if (f[n][j]) {
            ans = j;
            break;
        }
    printf("%d\n", ans);


    return 0;
}
