#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 20, INF = 0x3f3f3f3f;
const double EPS = 1e-7; // **

int n, m, dp[1048580], left[MAXN][MAXN];
double x[MAXN], y[MAXN];
inline int dcmp(const double &a, const double &b) { // *****
    return (fabs(a - b) < EPS) ? 0 : ((a < b) ? -1 : 1);
}
inline bool in(const int &a, const int &s) {
    return (s >> a) & 1;
}

int main() {
    int t, i, j, k, s, u;
    double a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        u = (1 << n) - 1;
        for (i = 0; i < n; ++i)
            scanf("%lf%lf", x + i, y + i);
        for (i = 0; i < n; ++i) {
            for (j = i + 1; j < n; ++j) {
                int &ki = left[i][j];
                a = ((y[i] / x[i]) - (y[j] / x[j])) / (x[i] - x[j]);
                if (dcmp(a, 0) != -1) {
                    ki = u;
                    continue;
                }
                b = y[i] / x[i] - a * x[i];
                ki = 0;
                for (k = 0; k < n; ++k) {
                    if (dcmp(a * x[k] * x[k] + b * x[k], y[k]) != 0)
                        ki |= 1 << k;  // **
                }
            }
        }
        dp[0] = 0;
        for (s = 1; s <= u; ++s) {
            dp[s] = INF;
            for (i = 0; !in(i, s); ++i);
            dp[s] = std::min(dp[s], dp[s ^ (1 << i)] + 1);
            for (j = i + 1; j < n; ++j)
                if (in(j, s))
                    dp[s] = std::min(dp[s], dp[s & left[i][j]] + 1);
        }
        printf("%d\n", dp[u]);
    }
    return 0;
}
