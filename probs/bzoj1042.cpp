#include <cstdio>

typedef long long ll;
const int m = 4;
int n, c[5], d[5];
ll f[100005] = {1};
int main() {
    static int i, j, s, cnt;
    static ll ans, a;
    for (i = 0; i < m; ++i)
        scanf("%d", c + i);
    scanf("%d", &n);
    for (i = 0; i < m; ++i)
        for (j = c[i]; j <= 100000; ++j) // order matters
            f[j] += f[j - c[i]];
    while (n--) {
        for (i = 0; i < m; ++i)
            scanf("%d", d + i);
        scanf("%d", &s);
        ans = 0;
        for (i = 1; i < 1 << m; ++i) {
            a = s, cnt = 0;
            for (j = 0; j < m; ++j)
                if ((i >> j) & 1)
                    a -= (ll)c[j] * (d[j] + 1), ++cnt;
            if (a >= 0)
                ans += f[a] * ((cnt & 1) ? 1 : -1);
        }
        printf("%lld\n", f[s] - ans);
    }
    return 0;
}
