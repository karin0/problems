#include <cstdio>
#include <algorithm>

const int N = 505, mo = 1024523;
int n, m, f[2][N][N];
char a[N], b[N];
inline void upd(int &x, const int d) {
    (x += d) %= mo;
}
int main() {
    static int i, j, k, mnk, p, np;
    static char s[N];
    scanf("%d%d", &n, &m);
    scanf("%s", s);
    for (i = 1; i <= n; ++i)
        a[i] = s[n - i];
    scanf("%s", s);
    for (i = 1; i <= m; ++i)
        b[i] = s[m - i];
    f[0][0][0] = 1;
    for (k = 0; ; ++k) {
        mnk = std::min(n, k);
        p = k & 1;
        np = p ^ 1;
        for (i = 0; i <= mnk; ++i) {
            for (j = 0; j <= mnk; ++j) {
                int &v = f[p][i][j];
                if (k == n + m && i == n && j == n) {
                    printf("%d\n", v); // ***
                    return 0;
                }
                if (v) {
                    if (b[k - i + 1] == b[k - j + 1])
                        upd(f[np][i][j], v);
                    if (b[k - i + 1] == a[j + 1])
                        upd(f[np][i][j + 1], v);
                    if (a[i + 1] == b[k - j + 1])
                        upd(f[np][i + 1][j], v);
                    if (a[i + 1] == a[j + 1])
                        upd(f[np][i + 1][j + 1], v);
                    v = 0;
                }
            }
        }
    }
    return 0;
}
