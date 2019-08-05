#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 200005;
char str[N];
int n, rk[N], sa[N], ht[N];
void build(int m) {
    static int fir[N], sec[N], tmp[N], cnt[N], i, l;
    static bool uni;
    ++n;
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
    --n;
}
int main() {
    static int i;
    scanf("%s", str);
    n = strlen(str);
    for (i = 0; i < n; ++i)
        str[n + i] = str[i];
    n += n;
    int w = n / 2;
    str[n] = 0;
    build(128);
    for (i = 1; i <= n; ++i)
        if (sa[i] < w)
            putchar(str[sa[i] + w - 1]);
    putchar('\n');
    return 0;
}

