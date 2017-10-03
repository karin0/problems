#include <cstdio>
#include <algorithm> 

const int MAXV = 1005, MAXN = 105;

int n, v, w[MAXN], c[MAXN], f[MAXV];

int main() {
    int i, j, ans = 0;
    scanf("%d%d", &v, &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", c + i, w + i);
    }

    for (i = 1; i <= n; ++i)
        for (j = v; j >= c[i]; --j)
            f[j] = std::max(f[j], f[j - c[i]] + w[i]);
    for (j = 0; j <= v; ++j)
        ans = std::max(ans, f[j]);
    printf("%d\n", ans);
    return 0;
}
