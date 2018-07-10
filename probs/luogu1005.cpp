// Luogu 1005
// QuJian DP
#include <cstdio>
#include <algorithm>
#define MAXN 85
#define Bigint int
#define POW2(x) (1<<(x))
using std::max;
using std::min;


int n, m, mat[MAXN][MAXN];
Bigint dp[MAXN][MAXN], ans0, ans; // 0 by default
int main() {
    scanf("%d%d", &n, &m);
    int len, i, j;
    for (int x = 1; x <= n; ++x) {
        for (int y = 1; y <= m; ++y) {
            scanf("%d", &mat[x][y]);    
        }
        // dp[i][j] is max score when [i..j] remains
        // total is [1..m]
        // how to reach dp[i][j]?
        //  - dp[i-1][j] or dp[i][j+1]
        // dp[i][j] = max(dp[i-1][j] + a[i-1] * 2 ^ (m - len), dp[i][j+1] + 2 ^ a[j + 1])
        // edge: dp[1][m] = 0
        ans0 = 0;
        dp[1][m] = 0;
        for (len = m - 1; len > 0; --len) {
            for (i = 1; (j = i + len - 1) <= m; ++i) {
                dp[i][j] = 0;
                if (i > 1) dp[i][j] = dp[i - 1][j] + mat[x][i - 1] * POW2(m - len);
                if (j < m) dp[i][j] = max(dp[i][j], dp[i][j + 1] + mat[x][j + 1] * POW2(m - len));
                if (len == 1) ans0 = max(ans0, dp[i][i] + mat[x][i] * POW2(m));
            }    
        }
        ans += ans0;
    }
    // printbigint(ans);
    printf("%d\n", ans);

}
