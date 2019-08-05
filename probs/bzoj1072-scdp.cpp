#include <cstdio>
#include <cstring>

const int L = 13, D = 1003, S = 1033;
int main() {
    static int ks, d, n, u, i, j, k, f[S][D], fac[L], cnt[L], ans;
    static char s[L];
    scanf("%d", &ks);
    fac[0] = 1;
    for (i = 1; i <= 9; ++i)
        fac[i] = fac[i - 1] * i;
    while (ks--) {
        scanf("%s%d", s, &d);
        n = strlen(s);
        u = 1 << n;
        for (i = 0; i <= 9; ++i)
            cnt[i] = 0;
        for (i = 0; i < n; ++i)
            ++cnt[s[i] - '0'];
        for (i = 0; i < u; ++i)
            for (j = 0; j < d; ++j) 
                f[i][j] = 0;
        f[0][0] = 1;
        for (i = 0; i < u; ++i)
            for (j = 0; j < d; ++j) if (f[i][j])
                for (k = 0; k < n; ++k) if (((i >> k) & 1) == 0)
                    f[i | (1 << k)][(j * 10 + s[k] - '0') % d] += f[i][j];
        ans = f[u - 1][0];
        for (i = 0; i <= 9; ++i)
            ans /= fac[cnt[i]];
        printf("%d\n", ans);
    }

    return 0;
}
