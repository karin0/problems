#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 53, INF = 0x7f7f7f7f;

char a[MAXN];
int n, f[MAXN][MAXN];

int main() {
    int i, j, k, l;
    scanf("%s", a + 1);
    n = strlen(a + 1);
    
    memset(f, INF, sizeof(f));
    for (i = 1; i <= n; ++i) {
        f[i][i] = 1;
    }
    for (l = 2; l <= n; ++l) {
        for (i = 1; (j = i + l - 1) <= n; ++i) {
            if (a[i] == a[j]) {
                if (l == 2)
                    f[i][j] = 1;
                else {
                    f[i][j] = std::min(
                            std::min(f[i + 1][j], f[i][j - 1]),
                            f[i + 1][j - 1] + 1);
                }
            } else {
                if (l == 2)
                    f[i][j] = 2;
                else {
                    if (a[i] == a[i + 1])
                        f[i][j] = std::min(f[i][j], f[i + 1][j]);
                    if (a[j] == a[j - 1])
                        f[i][j] = std::min(f[i][j], f[i][j - 1]);
                    if (f[i][j] == INF)
                        for (k = i; k < j; ++k)
                            f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
                }
            }
        }
    }
    
    printf("%d\n", f[1][n]);

    return 0;
}
