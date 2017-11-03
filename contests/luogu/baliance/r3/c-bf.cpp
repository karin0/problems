#include <cstdio>
#define LC(o) ((o) << 1)
#define RC(o) (((o) << 1) | 1)

typedef long long ll;
const int MAXN = 500005;
int n;
ll a[MAXN];

ll qpow(ll x, ll k) {
    static ll res;
    for (res = 1; k; k >>= 1, x = x * x)
        if (k & 1)
            res = res * x;
    return res;
}

namespace bf {
    void update(int l, int r, int x) {
        static int i;
        for (i = l; i <= r; ++i)
            a[i] += x;
    }
    int query(int l, int r, int x) {
        static int i;
        static ll res;
        if (x == 2)
            return a[l] & 1;
        else if (x == 1)
            return 0;
        res = a[r];
        for (i = r - 1; i > l; --i)
            res = qpow(a[i], res);
        if (r > l)
            res = qpow(a[l] % x, res);
        return res % x;
    }
}
namespace segt {
    struct Seg {
        int l, r;
        ll sum, ta;
    } st[MAXN * 4];
    void build(int o, int l, int r) {
        Seg &seg = st[o];
        seg.l = l;
        seg.r = r;
        seg.ta = 0;
        if (l == r) {
            seg.sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(LC(o), l, mid);
        build(RC(o), mid + 1, r);
        seg.sum = st[LC(o)].sum + st[RC(o)].sum;
    }
    void push_down(int o) {
        Seg &seg = st[o];
        if (seg.r >= seg.l || seg.ta == 0)
            return;
        Seg &lc = st[LC(o)], &rc = st[RC(o)];
        lc.ta += seg.ta;
        lc.sum += seg.ta * (lc.r - lc.l + 1);
        rc.ta += seg.ta;
        rc.sum += seg.ta * (rc.r - rc.l + 1);
        seg.ta = 0;
    }
    void update(int o, int l, int r, int x) {
        Seg &seg = st[o];
        if (l <= seg.l && seg.r <= r) {
            seg.ta += x;
            seg.sum += (ll)x * (seg.r - seg.l + 1);
            return;
        }
        push_down(o);
        int mid = (seg.l + seg.r) >> 1;
        if (l <= mid)
            update(LC(o), l, r, x);
        if (r >= mid + 1)
            update(RC(o), l, r, x);
        seg.sum = st[LC(o)].sum + st[RC(o)].sum;
    }
    ll query(int o, int i) {
        Seg &seg = st[o];
        if (i == seg.l && i == seg.r)
            return seg.sum;
        push_down(o);
        int mid = (seg.l + seg.r) >> 1;
        if (i <= mid)
            return query(LC(o), i);
        else
            return query(RC(o), i);
    }
    int solve(int l, int r, int x) {
        static int i;
        static ll res;
        if (x == 2)
            return query(1, l) & 1;
        else if (x == 1)
            return 0;
        res = query(1, r);
        for (i = r - 1; i > l; --i)
            res = qpow(query(1, i), res);
        if (r > l)
            res = qpow(query(1, l) % x, res);
        return res % x;
    }
}

int main() {
    static int i, kase, opt, l, r, x, m;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    if (n > 8000 || m > 8000) {
        segt::build(1, 1, n);
        for (kase = 1; kase <= m; ++kase) {
            scanf("%d%d%d%d", &opt, &l, &r, &x);
            if (opt == 1)
                segt::update(1, l, r, x);
            else
                printf("%d\n", segt::solve(l, r, x));
        }
    } else { // Bao Li
        for (kase = 1; kase <= m; ++kase) {
            scanf("%d%d%d%d", &opt, &l, &r, &x);
            if (opt == 1)
                bf::update(l, r, x);
            else
                printf("%d\n", bf::query(l, r, x));
        }
    }

    return 0;
}
