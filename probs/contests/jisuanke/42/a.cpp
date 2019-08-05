#include <cstdio>
#include <algorithm>

const int MAXN = 100005, MAXM = 1000005;

int n, m, inc[MAXN];

int main() {
    int i, x, ans = 0, lx = -1;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        inc[i] = i;
    for (i = 1; i <= m; ++i) {
        scanf("%d", &x);
        if (x != lx)
            ++ans, lx = x;
        std::swap(inc[x], inc[x + 1]);
    }
    for (i = 1; i <= n; ++i) {
        printf("%d ", inc[i]);
    }
    printf("\n%d\n", ans);

    return 0;
}
