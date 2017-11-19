#include <cstdio>
#include <cstring>
#include <algorithm>

const int MAXN = 203, INF = 0x7f7f7f7f;

int n;
struct Thu {
    int a, b;
} a[MAXN];
inline bool qaq(const Thu &x, const Thu &y) {
    return x.b > y.b;
}
int f[MAXN][MAXN * MAXN], sa[MAXN];

int main() {
    int i, j, ans = INF;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", &a[i].a, &a[i].b);
    std::sort(a + 1, a + n + 1, qaq);
    for (i = 1; i <= n; ++i)
        sa[i] = sa[i - 1] + a[i].a;

    memset(f, INF, sizeof(f));
    f[0][0] = 0;
    for (i = 1; i <= n; ++i) {
        for (j = 0; j <= sa[i]; ++j) {
            f[i][j] = std::max(f[i - 1][sa[i] - j], j + a[i].b);
            if (a[i].a <= j)
                f[i][j] = std::min(f[i][j], std::max(f[i - 1][j - a[i].a], j + a[i].b));
        }
    }
    for (j = 0; j <= sa[n]; ++j)
        ans = std::min(ans, f[n][j]);
    printf("%d\n", ans);

    return 0;
}
