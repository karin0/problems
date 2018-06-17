#include <cstdio>
#include <algorithm>
#define MAXN 16
#define MAXS 4100
#define ILLEGAL1(s, i) (((s) & (s << 1)) || (((s) | flats[(i)]) != flats[(i)]))
#define ILLEGAL2(s, t) ((s) & (t))
const int MOD = 100000000;
int m, n;
// int ans;
int ans;
int flats[MAXN];
int dp[MAXN][MAXS];

int main() {
    /* 
     dp[i][s] := 第 n 行状态为 s 时前 n 行的最大方案数
     dp[i][s] = sum{dp[i - 1][t] | t, (s, t) are legal}
     */
    scanf("%d%d", &n, &m); // n 行 m 列
    int i, j, s, t, scnt = (1 << m);
    for (i = 1; i <= n; ++i) {
        for (j = 0; j < m; ++j) {
            scanf("%d", &t);
            if (t) flats[i] |= (1 << j); // Actually "j" - 1
        }
    }
    for (i = 1; i <= n; ++i) {
        for (s = 0; s < scnt; ++s) {
            if (ILLEGAL1(s, i)) continue;
            if (i == 1) {
                dp[i][s] = 1;
            } else { 
                for (t = 0; t < scnt; ++t) {
                    if (ILLEGAL2(s, t) || ILLEGAL1(t, i - 1)) continue;
                    dp[i][s] += dp[i - 1][t];
                    if (dp[i][s] > MOD) dp[i][s] -= MOD;
                }
            }
            if (i == n) {
                ans += dp[i][s];
                if (ans > MOD) ans -= MOD;
            }
        }
    }
    printf("%d", ans);

}
