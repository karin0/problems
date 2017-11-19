#include <cstdio>
#include <algorithm>
#define MAXN 310
using std::max;

// f[i][x][y]: max weight of a matrix whose right border is (i, x) <-> (i, y)
// f[i][x][y] = max{
// f[i - 1][x][y] + sum[i][x..y],
// sum[i][x..y]
// }

int n, a[MAXN][MAXN], sum[MAXN][MAXN], dp[MAXN][MAXN][MAXN], ans = -2147483600;
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            scanf("%d", &a[i][j]);
            sum[i][j] = sum[i][j - 1] + a[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int x = 1; x <= n; ++x) {
            for (int y = x; y <= n; ++y) {
                dp[i][x][y] = max(dp[i - 1][x][y], 0) + sum[i][y] - sum[i][x - 1];
                ans = max(ans, dp[i][x][y]);
            }
        }
    }
    printf("%d\n", ans);
    
    return 0;
}
