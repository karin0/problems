#include <cstdio>
#include <algorithm>

const int MAXN = 10005;
int n, m, r[MAXN];

// 转化为选取一个集合，然后考虑各点对答案的贡献
int main() {
    static int i, u, v, w, ans;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%d", r + i);
        ans -= r[i];
        r[i] <<= 1;
    }
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        r[u] += w;
        r[v] += w;
        ans -= w;
    }
    std::sort(r + 1, r + n + 1);
    for (i = n; i >= 1; i -= 2) {
        ans += r[i];
    }
    printf("%d\n", ans);

    return 0;
}
