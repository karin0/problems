#include <cstdio>

const int MAXN = 33, MAXM = 23;
int n, m, p, ans, u;
int f[MAXN][1 << 20], det[MAXN];

int cnt1(int s) {
    static int res;
    for (res = 0; s; s >>= 1)
        res += s & 1;
    return res;
}

int main() {
    static int i, j, s;
    scanf("%d%d%d", &n, &m, &p);
    u = 1 << n;
    for (i = 1; i <= n; ++i)
        det[i] = -1;
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &j, &s);
        det[j] = s - 1;
    }
    if (n == 1) {
        printf("%d\n", n - det[1]);
        return 0;
    }
    if (det[1] == -1) {
        for (j = 0; j < n; ++j)
            f[1][1 << j] = 1;
    } else
        f[1][1 << det[1]] = 1;
    for (i = 2; i <= n; ++i) {
        if (det[i] == -1) {
            for (s = 3; s < u; ++s) {
                if (cnt1(s) == i) {
                    for (j = 0; j < n; ++j)
                        if ((s >> j) & 1) {
                            f[i][s] += f[i - 1][s & (~(1 << j))];
                            if (f[i][s] >= p)
                                f[i][s] -= p;
                        }
                    if (i == n) {
                        ans += f[i][s];
                        if (ans >= p)
                            ans -= p;
                    }
                }
            }
        } else {
            for (s = 3; s < u; ++s) {
                if (cnt1(s) == i) {
                    for (j = det[i]; j < n; ++j) {
                        if ((s >> j) & 1) {
                            f[i][s] += f[i - 1][s & (~(1 << j))];
                            if (f[i][s] >= p)
                                f[i][s] -= p;
                        } else
                            break;
                    }
                    if (i == n) {
                        ans += f[i][s];
                        if (ans >= p)
                            ans -= p;
                    }
                }
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}
