#include <cstdio>

const int N = 3004;
typedef long long ll;
int n, m, s[N];
ll f[2][N];
inline double slope(int p, int q, int j) {
    return (double)(f[j][p] + (ll)s[p] * s[p] - f[j][q] - (ll)s[q] * s[q]) / (s[p] - s[q]);
}
int main() {
    static int i, j, k;
    static ll q[N], *hd, *tl;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &k);
        s[i] = s[i - 1] + k;
        f[1][i] = (ll)s[i] * s[i]; // ***
    }
    for (j = 2; j <= m; ++j) {
        hd = q + 1, tl = q;
        *(++tl) = 0;
        for (i = 1; i <= n; ++i) {
            while (tl - hd + 1 > 1 && slope(*hd, *(hd + 1), (j & 1) ^ 1) < 2 * s[i])
                ++hd;
            k = *hd;
            f[j & 1][i] = f[(j & 1) ^ 1][k] + (ll)(s[i] - s[k]) * (s[i] - s[k]);
            while (tl - hd + 1 > 1 && slope(*(tl - 1), *tl, (j & 1) ^ 1) > slope(*tl, i, (j & 1) ^ 1))
                --tl;
            *(++tl) = i;
        }
    }
    printf("%lld\n", (ll)m * f[m & 1][n] - (ll)(s[n] * s[n]));
    // printf("%lld\n", f[n][m]);

    return 0;
}
