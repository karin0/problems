// unreasonable
#include <cstdio>
#include <algorithm>
#define MAXN 70
using std::max;

int m, n;
int map[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN][MAXN];

int main() {
    scanf("%d%d", &m, &n);
    int x, y;
    for (x = 1; x <= m; ++x) {
        for (y = 1; y <= n; ++y) {
            scanf("%d", &map[x][y]);
        }
    }
    int i, j;
    for (x = 1; x <= m; ++x) {
        for (y = 1; y <= n; ++y) {
            for (i = 1; i <= m; ++i) {
                for (j = 1; j <= n; ++j) {
                    if (x + y != i + j) continue;
                    dp[x][y][i][j] = max(max(dp[x - 1][y][i - 1][j], dp[x - 1][y][i][j - 1]), max(dp[x][y - 1][i][j - 1], dp[x][y - 1][i - 1][j])) + map[x][y] + ((x == i) ? 0 : map[i][x + y - i]);
                }
            }
        }    
    
    }
    printf("%d\n", dp[m][n][m][n]);

    return 0;
}
