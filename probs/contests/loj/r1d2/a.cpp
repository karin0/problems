#include <cstdio>

int n, m, x, c, mk, k, d, i, j, cv;
bool g[503][503];
int main() {
    scanf("%d", &x);
    for (m = 1; m <= 500; ++m) {
        for (n = 2; n <= 500 - m; ++n) {
            k = (x - m * (n - 1)) / m;
            if (m * (n - 1 + k) < x)
                ++k;
            if (k < 0 || k > (n * (n - 1) / 2) - (n - 1))
                continue;
            c = m * (n - 1 + k);
            if (c >= x) {
                d = c - x;
                if (d > m * n)
                    continue;
                for (i = 1; i <= m; ++i) {
                    for (j = 1; j <= n; ++j) {
                        if (d > 0)
                            --d;
                        else
                            g[j][n + i] = true;
                    }
                }
                for (i = n; i >= 1; --i) {
                    for (j = n - 1; j >= 1; --j) {
                        if (k > 0)
                            g[j][i] = true, --k;
                        else
                            break;
                    }
                }
                for (i = 1; i < n; ++i)
                    g[i][i + 1] = true;
                cv = n + m;
                printf("%d\n", cv);
                for (i = 1; i < cv; ++i) {
                    for (j = 1; i + j <= cv; ++j) {
                        putchar(g[i][i + j] ? '1' : '0');
                        putchar(' ');
                    }
                    putchar('\n');
                }
                return 0;
            }
        }
    }

    return 0;
}
