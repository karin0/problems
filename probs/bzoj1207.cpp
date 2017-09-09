#include <cstdio>
#include <algorithm>

const int MAXM = 1e4 + 5;

int n, m, f[MAXM], ans;
struct Mole {
    long long t;
    int x, y;
} a[MAXM];

inline bool reach(const Mole &x, const Mole &y) {
    return std::abs(x.x - y.x) + std::abs(x.y - y.y) <= y.t - x.t;
}

int main() {
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%lld%d%d", &a[i].t, &a[i].x, &a[i].y);
        f[i] = 1;
        for (j = 1; j < i; ++j) {
            if (reach(a[j], a[i])) {
                f[i] = std::max(f[i], f[j] + 1);
            }
        }
        ans = std::max(ans, f[i]);
    }

    printf("%d\n", ans);
    return 0;
}
