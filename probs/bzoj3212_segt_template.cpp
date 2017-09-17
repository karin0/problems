#include <cstdio>
#define MID(x, y) (((x) + (y)) >> 1)
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)

typedef long long ll;
const int MAXN = 100007;

int n;
ll a[MAXN];

struct Seg {
    int l, r;
    ll sum, ta;
} st[MAXN * 4];
inline void build(int o, int l, int r) {
    Seg &seg = st[o];
    seg.l = l;
    seg.r = r;
    seg.ta = 0;
    if (l == r) {
        seg.sum = a[l];
        return;
    }
    int mid = MID(l, r);
    build(LC(o), l, mid);
    build(RC(o), mid + 1, r);
    seg.sum = st[LC(o)].sum + st[RC(o)].sum;
}
inline void push_down(int o) {
    Seg &seg = st[o];
    if (seg.l < seg.r) {
        Seg &lc = st[LC(o)], &rc = st[RC(o)];
        lc.ta += seg.ta;
        lc.sum += seg.ta * (lc.r - lc.l + 1);
        
        rc.ta += seg.ta;
        rc.sum += seg.ta * (rc.r - rc.l + 1);
    }
    seg.ta = 0;
}
inline void push_up(int o) {
    Seg &seg = st[o], &lc = st[LC(o)], &rc = st[RC(o)];
    seg.sum = lc.sum + rc.sum;
}
inline void update(int o, int l, int r, int v) {
    Seg &seg = st[o];
    if (seg.r < l || r < seg.l)
        return;
    push_down(o);
    if (l <= seg.l && seg.r <= r) {
        seg.ta = v;
        seg.sum += v * (seg.r - seg.l + 1);
        return;
    }
    update(LC(o), l, r, v);
    update(RC(o), l, r, v);
    push_up(o);
}
inline ll query(int o, int l, int r) {
    Seg &seg = st[o];
    if (seg.r < l || r < seg.l)
        return 0;
    push_down(o);
    if (l <= seg.l && seg.r <= r)
        return seg.sum;
    ll res = query(LC(o), l, r) + query(RC(o), l, r);
    return res;
}

int main() {
    int m, i, l, r;
    ll x;
    char opt[3];
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    build(1, 1, n);
    while (m--) {
        scanf("%s%d%d", opt, &l, &r);
        if (opt[0] == 'C') {
            scanf("%lld", &x);
            update(1, l, r, x);
        } else
            printf("%lld\n", query(1, l, r));
    }

    return 0;
}
