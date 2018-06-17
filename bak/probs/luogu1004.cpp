#include <cstdio>
#include <algorithm>
#define MAXN 20
using std::max;

int n;
int map[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN];

int main() {
    scanf("%d", &n);
    int x, y, v;
    for (;;) {
        scanf("%d%d%d", &x, &y, &v);
        map[x][y] = v;
        if (!v) break;
    }
    int j;
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= n; ++y) {
            for (int i = 1; i <= n; ++i) {
                j = x + y - i;
                dp[x][y][i] = max(max(dp[x - 1][y][i], dp[x - 1][y][i - 1]), max(dp[x][y - 1][i], dp[x][y - 1][i - 1])) + map[x][y] + ((x == i && y == j) ? 0 : map[i][j]);
            }    
        }    
    
    }
    printf("%d\n", dp[n][n][n]);

    return 0;
}
