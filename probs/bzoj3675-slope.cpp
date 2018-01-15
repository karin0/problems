#include <cstdio>
#include <algorithm>

const int N = 100005;
typedef long long ll;
int n, m, s[N], j;
ll f[2][N];
inline bool less(int p, int q, int x) { // assert p <= q
    if (p > q)
        std::swap(p, q);
    return (f[j ^ 1][p] - (ll)s[p] * s[p] - f[j ^ 1][q] + (ll)s[q] * s[q]) > ((ll)(s[p] - s[q]) * x);
}
inline bool less_slope(int p1, int q1, int p2, int q2) { // assert both p <= q
    return ((f[j ^ 1][p1] - (ll)s[p1] * s[p1] - f[j ^ 1][q1] + (ll)s[q1] * s[q1]) * ((ll)(s[p2] - s[q2]))) < 
           ((f[j ^ 1][p2] - (ll)s[p2] * s[p2] - f[j ^ 1][q2] + (ll)s[q2] * s[q2]) * ((ll)(s[p1] - s[q1])));
}
int main() {
    static int i, jh, k, cnt;
    static ll q[N], *hd, *tl;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &k);
        if (k)
            ++cnt, s[cnt] = s[cnt - 1] + k;
    }
    n = cnt;
    for (jh = 1; jh <= m; ++jh) {
        j = jh & 1;
        hd = q + 1, tl = q;
        // *(++tl) = 0;
        for (i = 1; i <= n; ++i) {
            while (tl - hd + 1 > 1 && !less(*hd, *(hd + 1), -s[i]))
                ++hd;
            k = *hd;
            f[j][i] = f[j ^ 1][k] + (ll)(s[i] - s[k]) * s[k];
            while (tl - hd + 1 > 1 && less_slope(*(tl - 1), *tl, *tl, i))
                --tl;
            *(++tl) = i;
        }
    }
    printf("%lld\n", f[m & 1][n]);

    return 0;
}
