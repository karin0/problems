#include <cstdio>
#include <cstring>
#include <algorithm>

using std::min;
const int MAXN = 503;

int n, m, t, k, ehp, atk;
int eatk[MAXN][MAXN];

int ans = 2147483647;
int f[MAXN][MAXN][12][7];
int datk[MAXN][MAXN][12][7];

inline int cnt(int a) {
    return (ehp % a) ? (ehp / a) : (ehp / a - 1);
}

int main() {
    int i, j, c, d, times, hurt, tmp1, tmp2;
    scanf("%d%d%d%d%d%d", &n, &m, &t, &k, &ehp, &atk);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            scanf("%d", &eatk[i][j]);
    memset(f, 0x7f, sizeof(f));
    times = cnt(atk);
    for (c = t; c >= 0; --c)
        for (d = k; d >= 1; --d)
            f[1][1][c][d] = 0;
    for (i = 1; i <= n; ++i) {
        for (j = 1; j <= m; ++j) {
            hurt = times * eatk[i][j];
            for (c = t; c >= 0; --c) {
                for (d = k; d >= 1; --d) {
                    int &ft = f[i][j][c][d];
                    int &datkt = datk[i][j][c][d];
                    if (d == k) { // 上一步未使用能力或刚好使用完能力
                        ft = min(ft, 
                                min(f[i - 1][j][c][d], f[i][j - 1][c][d]) + hurt);
                        if (c < t)
                            ft = min(ft,
                                min(f[i - 1][j][c + 1][1] + cnt(atk + datk[i - 1][j][c + 1][1] + eatk[i][j]) * eatk[i][j],
                                    f[i][j - 1][c + 1][1] + cnt(atk + datk[i][j - 1][c + 1][1] + eatk[i][j]) * eatk[i][j])
                                   );
                    } else { // 上一步使用了能力,下一步还要使用
                        tmp1 = f[i - 1][j][c][d + 1] + cnt(atk + datk[i - 1][j][c][d + 1] + eatk[i][j]) * eatk[i][j];
                        tmp2 = f[i][j - 1][c][d + 1] + cnt(atk + datk[i][j - 1][c][d + 1] + eatk[i][j]) * eatk[i][j];
                        if (tmp1 < tmp2) {
                            if (tmp1 <= ft)
                                ft = tmp1, datkt = datk[i - 1][j][c][d + 1] + eatk[i][j];
                        } else if (tmp2 <= ft)
                                ft = tmp2, datkt = datk[i][j - 1][c][d + 1] + eatk[i][j];
                    }
                    if (i == n && j == m) {
                        ans = min(ans, ft);
                    }
                }
            }
        }
    }
    printf("%d\n", ans);
}

/*


考虑没有能力：
f(x, y) = min{f(x - 1, y), f(x, y - 1)} + floor(ehp / atk) * eatk(x, y)

f(x, y, c, d, datk) // 到达 (x, y)，还能使用 c 次能力,当前还能凭能力移动 d 步(若走上一步时未使用能力,d = k),能力带来的攻击力增量为 datk 时受到的最小伤害
f(x, y, c, d) = min{f(x - 1, y, )}
*/
