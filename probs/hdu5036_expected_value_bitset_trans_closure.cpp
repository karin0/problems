#include <cstdio>
#include <bitset>

const int MAXN = 1005;

int n;
std::bitset<MAXN> g[MAXN];

inline void floyd() {
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            if (g[i][k])
                g[i] |= g[k];
}

int main() {
    int t, d, i, u, v, k;
    double ans;
    scanf("%d", &t);
    for (int kase = 1; kase <= t; ++kase) {
        scanf("%d", &n);
        for (u = 1; u <= n; ++u) {
            g[u].reset();
            // g[u][u] = 1;
            g[u].set(u);
            scanf("%d", &d);
            for (i = 1; i <= d; ++i) {
                scanf("%d", &v);
                g[u].set(v);
            }
        }
        floyd();

        ans = 0.0;
        for (v = 1; v <= n; ++v) {
            k = 0;
            for (u = 1; u <= n; ++u)
                if (g[u][v])
                    ++k;
            ans += 1.0 / k;
        }
        printf("Case #%d: %.5lf\n", kase, ans);
    }
    return 0;
}
