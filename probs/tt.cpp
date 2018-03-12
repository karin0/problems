#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))


typedef long long ll;
const int N = 100333;
int bs, dv[N];
struct Query {
    int l, r;
    ll *ans;
    bool operator < (const Query &rhs) const {
        return dv[l] < dv[rhs.l] || (dv[l] == dv[rhs.l] && r < rhs.r);
    }
} qwq[N];
int qpow(ll a, int n, int p) {
    static ll res;
    for (res = 1; n; a = a * a % p, n >>= 1)
        if (n & 1)
            res = res * a % p;
    return res;
}
inline ll calc(ll x) {
    return (x * (x - 1)) >> 1;
}
int main() {
    static int p, n, m, a[N], i, inv10, h[N], *end, c[N], l = -1, r = -1, g[N];
    static ll ans[N], res, t, f[N];
    static char s[N];
    scanf("%d%s%d", &p, s, &m);
    if (p == 2) {
        for (i = 0; s[i]; ++i) {
            if (((s[i] - '0') & 1) == 0)
                f[i] += i, ++g[i];
            f[i + 1] = f[i];
            g[i + 1] = g[i];
        }
        re (i, 0, m) {
            scanf("%d%d", &l, &r);
            l -= 2, --r;
            printf("%lld\n", f[r] - f[l] - (ll)l * (g[r] - g[l]));
        }
        return 0;
    } else if (p == 5) {
        for (i = 0; s[i]; ++i) {
            if (s[i] == '5' || s[i] == '0')
                f[i] += i, ++g[i];
            f[i + 1] = f[i];
            g[i + 1] = g[i];
        }
        re (i, 0, m) {
            scanf("%d%d", &l, &r);
            l -= 2, --r;
            printf("%lld\n", f[r] - f[l] - (ll)l * (g[r] - g[l]));
        }
        return 0;
    }
    a[0] = s[0] - '0';
    for (i = 1; s[i]; ++i)
        a[i] = (a[i - 1] * 10ll + (s[i] - '0')) % p;
    n = i;
    inv10 = qpow(10, p - 2, p);
    for (i = 0, t = 1; i < n; ++i, t = t * inv10 % p)
        h[i] = a[i] = t * a[i] % p;
    std::sort(h, h + n);
    end = std::unique(h, h + n);
    re (i, 0, n)
        a[i] = std::lower_bound(h, end, a[i]) - h;
    re (i, 0, m) {
        Query &q = qwq[i];
        scanf("%d%d", &q.l, &q.r);
        q.l -= 2, --q.r;
        q.ans = &ans[i];
    }
    bs = sqrt(2.0 * (double)n * n / m);
    re (i, 0, n)
        dv[i] = i / bs;
    std::sort(qwq, qwq + m);
    const Query &q = qwq[0];
    l = q.l, r = q.r;
    rep (i, l, r)
        res -= calc(c[a[i]]), res += calc(++c[a[i]]);
    *q.ans = res;
    re (i, 1, m) {
        const Query &q = qwq[i];
        while (l < q.l)
            res -= calc(c[a[l]]--), res += calc(c[a[l++]]);
        while (q.r < r)
            res -= calc(c[a[r]]--), res += calc(c[a[r--]]);
        while (q.l < l)
            res -= calc(c[a[--l]]), res += calc(++c[a[l]]);
        while (r < q.r)
            res -= calc(c[a[++r]]), res += calc(++c[a[r]]);
        *q.ans = res;
    }
    re (i, 0, m)
        printf("%lld\n", ans[i]);

    return 0;
}
