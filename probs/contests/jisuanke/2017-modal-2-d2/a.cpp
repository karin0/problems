// f(i, j) = max {
//                  f(i - 1, j) - abs(sum(g(i - 1, j), i)) + abs(sum(j, k))   (i != j)
//
// f(i, j, k) = max{ f(i, x, k) }
//                  f(i - 1, j) - abs(sum(g(i - 1, j), i)) + abs(sum(j, k))   (i != j)
#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 803, MAXM = 83;

int n, m;
double a[MAXN], s[MAXN], f[MAXN][MAXM], g[MAXN][MAXM];

inline double sum(int x, int y) {
    return (y >= x && x >= 1) ? (s[y] - s[x - 1]) : 0;
}

int main() {
    int i, j, r;
    double x, y;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%lf", a + i);
    for (i = 1; i <= n; ++i)
        scanf("%lf", &x), a[i] -= x, s[i] = s[i - 1] + a[i], f[i][1] = fabs(s[i]), g[i][1] = 1;

    for (i = 2; i <= n; ++i) {
        r = std::min(i, m);
        for (j = 2; j <= r; ++j) {
            x = f[i - 1][j] - fabs(sum(g[i - 1][j], i - 1)) + fabs(sum(g[i - 1][j], i));
            y = f[i - 1][j - 1] + fabs(a[i]);
            if (x < y)
                f[i][j] = y, g[i][j] = i;
            else
                f[i][j] = x, g[i][j] = g[i - 1][j];
        }
    }
    printf("%.6lf\n", f[n][m]);
    return 0;
}
