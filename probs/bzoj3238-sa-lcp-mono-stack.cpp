#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long ll;
const int N = 500005;

char s[N];
int n, rk[N], sa[N], ht[N];
void build(int m) {
    static int fir[N], sec[N], tmp[N], cnt[N], i, l;
    static bool uni;
    ++n;
    s[n - 1] = 0;
    std::fill(cnt, cnt + m, 0);
    for (i = 0; i < n; ++i)
        ++cnt[s[i]];
    for (i = 1; i < m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = 0; i < n; ++i)
        rk[i] = cnt[s[i]] - 1;
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
void init_ht() {
    static int i, j, k;
    for (k = 0, i = 0; i < n; ++i) {
        if (k)
            --k;
        for (j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
        ht[rk[i]] = k;
    }
}
int sta[N], cnt;
int main() {
    static int i, l[N];
    static ll ans;
    scanf("%s", s);
    n = strlen(s);
    build(128);
    init_ht();
    // for (i = 0; i <= n; ++i)
    //    printf("rk[%d] = %d, sa[%d] = %d, ht[%d] = %d\n",i,rk[i],i,sa[i],i,ht[i]);
    for (i = 2; i <= n; ++i) {
        while (cnt > 0 && ht[sta[cnt]] > ht[i])
            --cnt;
        l[i] = cnt ? i - sta[cnt] : (i - 1);
        sta[++cnt] = i;
    }
    cnt = 0;
    for (i = n; i >= 2; --i) {
        while (cnt > 0 && ht[sta[cnt]] >= ht[i])
            --cnt;
        ans += (ll)(cnt ? sta[cnt] - i : (n - i + 1)) * l[i] * ht[i];
        sta[++cnt] = i;
    }
    printf("%lld\n", ((ll)n * n - 1) * n / 2 - 2 * ans);

    return 0;
}

