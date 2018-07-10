// それは違う！
#include <cstdio>
#include <algorithm>

const int MAXN = 504, INF = 0x7f7f7f7f;
int n, m = 1, a[MAXN], b[MAXN], c[MAXN], f[MAXN][MAXN];

inline int times(int x) {
    return x >= 2 ? 1 : 2;
}

int main() {
    int i, j, k, l;
    scanf("%d", &n);

    scanf("%d", a + 1);
    b[1] = a[1];
    c[1] = 1;
    for (i = 2; i <= n; ++i) {
        scanf("%d", a + i);
        if (a[i] != a[i - 1]) {
            f[m][m] = (c[m] >= 2 ? 1 : 2);
            b[++m] = a[i];
        }
        ++c[m];
    }
    f[m][m] = (c[m] >= 2 ? 1 : 2);

    for (l = 2; l <= m; ++l) {
        for (i = 1; (j = i + l - 1) <= m; ++i) {
            f[i][j] = INF;
            if (b[i] == b[j]) {
                f[i][j] = std::min(f[i][j], std::min(std::min(f[i][j - 1] + times(c[j]), f[i + 1][j] + times(c[i])), f[i + 1][j - 1] + (c[i] + c[j] < 3)));
            }
            for (k = i; k < j; ++k) {
                f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
            }
        }
    }
    
    printf("%d\n", f[1][m]);

    return 0;
}
