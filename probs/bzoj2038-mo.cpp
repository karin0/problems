#include <cstdio>
#include <cmath>
#include <algorithm>

typedef long long ll;
const int N = 50005;
int n, bsiz;
struct Query {
    int l, r;
    ll *ret;
    
    bool operator < (const Query &rhs) const {
        int p = l / bsiz, q = rhs.l / bsiz;
        return p < q || (p == q && r < rhs.r);
    }
} qwq[N];
inline ll calc(const ll x) {
    return x * (x - 1);
}
ll gcd(const ll a, const ll b) {
    return b ? gcd(b, a % b) : a;
}
int main() {
    static int m, i, a[N], cnt[N], l, r;
    static ll len[N], ret[N], ans, g;
    scanf("%d%d", &n, &m);
    bsiz = floor(sqrt(n) + 0.5);
    for (i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    for (i = 0; i < m; ++i) {
        scanf("%d%d", &l, &r);
        qwq[i].l = l - 1, qwq[i].r = r - 1, qwq[i].ret = &ret[i];
        len[i] = calc(r - l + 1);
    }
    std::sort(qwq, qwq + m);
    l = qwq[0].l, r = qwq[0].r;
    for (i = l; i <= r; ++i) {
        ans -= calc(cnt[a[i]]);
        ans += calc(++cnt[a[i]]);
    }
    *qwq[0].ret = ans;
    for (i = 1; i < m; ++i) {
        const Query &q = qwq[i];
        while (q.l < l)
            --l, ans -= calc(cnt[a[l]]), ans += calc(++cnt[a[l]]);
        while (r < q.r)
            ++r, ans -= calc(cnt[a[r]]), ans += calc(++cnt[a[r]]);
        while (l < q.l)
            ans -= calc(cnt[a[l]]), ans += calc(--cnt[a[l]]), ++l;
        while (q.r < r)
            ans -= calc(cnt[a[r]]), ans += calc(--cnt[a[r]]), --r;
        *q.ret = ans;
    }
    for (i = 0; i < m; ++i) {
        g = gcd(ret[i], len[i]);
        printf("%lld/%lld\n", ret[i] / g, len[i] / g);
    }

    return 0;
}
