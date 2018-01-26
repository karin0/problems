#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100005;
char str[N];
int n, rk[N], sa[N], ht[N];
void build(int m) {
    static int fir[N], sec[N], tmp[N], cnt[N], i, l;
    static bool uni;
    n = strlen(str) + 1;
    str[n - 1] = 0;
    std::fill(cnt, cnt + m, 0);
    for (i = 0; i < n; ++i)
        ++cnt[str[i]];
    for (i = 1; i < m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = 0; i < n; ++i)
        rk[i] = cnt[str[i]] - 1;
    for (l = 1; l < n; l <<= 1) {
        for (i = 0; i < n; ++i)
            fir[i] = rk[i], sec[i] = (i + l < n) ? rk[i + l] : 0;
        std::fill(cnt, cnt + n, 0);
        for (i = 0; i < n; ++i)
            ++cnt[sec[i]];
        for (i = 1; i < n; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; --i)
            tmp[--cnt[sec[i]]] = i;
        std::fill(cnt, cnt + n, 0);
        for (i = 0; i < n; ++i)
            ++cnt[fir[i]];
        for (i = 1; i < n; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; --i)
            sa[--cnt[fir[tmp[i]]]] = tmp[i];
        uni = true;
        rk[sa[0]] = 0;
        for (i = 1; i < n; ++i) {
            rk[sa[i]] = rk[sa[i - 1]];
            if (fir[sa[i]] == fir[sa[i - 1]] && sec[sa[i]] == sec[sa[i - 1]])
                uni = false;
            else
                ++rk[sa[i]];
        }
        if (uni)
            break;
    }
}
void init_ht() {
    static int i, j, k;
    for (k = 0, i = 0; i < n - 1; ++i) {
        if (k)
            --k;
        j = sa[rk[i] - 1];
        while (str[i + k] == str[j + k])
            ++k;
        ht[rk[i]] = k;
    }
}
int main() {
    static int i;
    scanf("%s", str);
    build(128);
    init_ht();
    --n;
    for (i = 1; i <= n; ++i)
        printf("%d%c", sa[i] + 1, i == n ? '\n' : ' ');
    for (i = 2; i <= n; ++i)
        printf("%d%c", ht[i], i == n ? '\n' : ' ');
    for (i = 0; i <= n; ++i)
        printf("str[%d] = %c, sa[%d] = %d, rk[%d] = %d, ht[%d] = %d\n", i, str[i], i, sa[i], i, rk[i], i, ht[i]);
    return 0;
}

