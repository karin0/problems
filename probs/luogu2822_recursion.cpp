#include <cstdio>
#include <algorithm>

const int MAXN = 2005;

int k;
int _c[MAXN][MAXN];
inline int c(int n, int m) {
    return _c[n][m] ? _c[n][m] : (_c[n][m] = (((n == m || n <= 1 || m <= 0) ? 1 : c(n - 1, m - 1) + c(n - 1, m)) % k));
}

int main() {
    int n, m, t, r, i, j, ans;
    scanf("%d%d", &t, &k);
    for (int qaq = 0; qaq < t; ++qaq) {
        ans = 0;
        scanf("%d%d", &n, &m);
        for (i = 0; i <= n; ++i) {
            r = std::min(i, m);
            for (j = 0; j <= r; ++j)
                if (c(i, j) == 0)
                    ++ans;
        }
        printf("%d\n", ans);
    }

    return 0;
}
