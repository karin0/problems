#include <cstdio>
#include <algorithm>
typedef long long ll;
const int MAXN = 200005, MOD = 19260817;
int n, x[MAXN], p[MAXN], sa[MAXN];

inline int f(int l, int r, int k, bool rt) {
    return ((rt ? -1 : 1) * (p[r] - p[l - 1] - (ll)x[k] * (sa[r] - sa[l - 1])) % MOD + MOD) % MOD;
}

int main() {
    static int i, m, t, l, r, res;
    scanf("%d%d", &n, &m);
    for (i = 2; i <= n; ++i) {
        scanf("%d", &t);
        x[i] = x[i - 1] + t % MOD;
        if (x[i] >= MOD)
            x[i] -= MOD;
    }
    for (i = 1; i <= n; ++i) {
        scanf("%d", &t);
        t %= MOD;
        sa[i] = sa[i - 1] + t;
        if (sa[i] >= MOD)
            sa[i] -= MOD;
        p[i] = p[i - 1] + ((ll)t * x[i]) % MOD;
        if (p[i] >= MOD)
            p[i] -= MOD;
    }
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &t, &l, &r);
        if (t > r || t < l)
            printf("%d\n", f(l, r, t, t > r));
        else {
            res = f(l, t - 1, t, true) + f(t + 1, r, t, false);
            if (res >= MOD)
                printf("%d\n", res - MOD);
            else
                printf("%d\n", res);
        }
    }

    return 0;
}
