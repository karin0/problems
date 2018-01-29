#include <cstdio>
#include <algorithm>

const int N = 63, C = 23;
int n, c1,c2, c3, mo;

int calc(int p[]) { // 计算置换 p 的不动点数
    static bool vis[N];
    static int i, j, k, l, t, f[C][C][C];
    std::fill(vis + 1, vis + n + 1, false);
    for (i = 0; i <= c1; ++i)
        for (j = 0; j <= c2; ++j)
            for (k = 0; k <= c3; ++k)
                f[i][j][k] = 0;
    f[0][0][0] = 1;
    for (l = 1; l <= n; ++l)
        if (!vis[l]) {
            for (t = 0, i = l; !vis[i]; i = p[i])
                vis[i] = true, ++t;
            for (i = c1; i >= 0; --i)
                for (j = c2; j >= 0; --j)
                    for (k = c3; k >= 0; --k) {
                        if (i >= t)
                            (f[i][j][k] += f[i - t][j][k]) %= mo;
                        if (j >= t)
                            (f[i][j][k] += f[i][j - t][k]) %= mo;
                        if (k >= t)
                            (f[i][j][k] += f[i][j][k - t]) %= mo;
                    }
        }
    return f[c1][c2][c3];
}
int qpow(int a, int x) {
    static int res;
    for (res = 1; x; x >>= 1, a = a * a % mo)
        if (x & 1)
            res = res * a % mo;
    return res;
}
int inv(int x) {
    return qpow(x, mo - 2);
}
int main() {
    static int m, p[N], i, j, ans;
    scanf("%d%d%d%d%d", &c1, &c2, &c3, &m, &mo);
    n = c1 + c2 + c3;
    for (i = 1; i <= m; ++i) {
        for (j = 1; j <= n; ++j)
            scanf("%d", p + j);
        (ans += calc(p)) %= mo;
    }
    for (i = 1; i <= n; ++i)
        p[i] = i;
    (ans += calc(p)) %= mo;
    printf("%d\n", ans * inv(m + 1) % mo);

    return 0;
}
