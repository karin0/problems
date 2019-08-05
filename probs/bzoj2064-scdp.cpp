#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 13, S = 1027;
int n, m, ua, ub, a[N], b[N], sa[S], sb[S], f[S][S], ca[S], cb[S];
int main() {
    static int i, j, s, t;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", a + i);
    scanf("%d", &m);
    for (i = 0; i < m; ++i)
        scanf("%d", b + i);
    memset(f, 0x3f, sizeof(f));
    ua = 1 << n, ub = 1 << m;
    for (i = 1; i < ua; ++i)
        for (j = 0; j < n; ++j)
            if ((i >> j) & 1)
                sa[i] += a[j], ++ca[i];
    for (i = 1; i < ub; ++i)
        for (j = 0; j < m; ++j)
            if ((i >> j) & 1) // ** **
                sb[i] += b[j], ++cb[i];
    for (i = 1; i < ua; ++i)
        for (j = 1; j < ub; ++j)
            if (sa[i] == sb[j]) {
                f[i][j] = ca[i] + cb[j] - 2;
                for (s = i & (i - 1); s; s = i & (s - 1))
                    for (t = j & (j - 1); t; t = j & (t - 1))
                        if (sa[s] == sb[t])
                            f[i][j] = std::min(f[i][j], f[s][t] + f[i - s][j - t]);
            }
    printf("%d\n", f[ua - 1][ub - 1]);
    return 0;
}
