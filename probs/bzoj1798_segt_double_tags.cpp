#include <cstdio>
#define MID(x, y) (((x) + (y)) >> 1)
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)

typedef long long ll;
const int MAXN = 100007;

int n;
ll mod, a[MAXN];

inline ll mod1(int x) {
    return x >= mod ? x - mod : x;
}
struct Seg {
    int l, r;
    ll sum, ta, tm;
} st[MAXN * 4];
inline void build(int o, int l, int r) {
    Seg &seg = st[o];
    seg.l = l;
    seg.r = r;
    seg.tm = 1;
    seg.ta = 0;
    if (l == r) {
        seg.sum = a[l] % mod;
        return;
    }
    int mid = MID(l, r);
    build(LC(o), l, mid);
    build(RC(o), mid + 1, r);
    seg.sum = mod1(st[LC(o)].sum + st[RC(o)].sum);
}
inline void push_down(int o) {
    Seg &seg = st[o];
    // 先乘后加，先乘后加，先乘后加
    if (seg.l < seg.r) {
        Seg &lc = st[LC(o)], &rc = st[RC(o)];
        lc.tm = (lc.tm * seg.tm) % mod;
        lc.ta = mod1((lc.ta * seg.tm) % mod + seg.ta);
        lc.sum = mod1((lc.sum * seg.tm) % mod + (seg.ta * (lc.r - lc.l + 1)) % mod);
        
        rc.tm = (rc.tm * seg.tm) % mod;
        rc.ta = mod1((rc.ta * seg.tm) % mod + seg.ta);
        rc.sum = mod1((rc.sum * seg.tm) % mod + (seg.ta * (rc.r - rc.l + 1)) % mod);
    }
    seg.tm = 1;
    seg.ta = 0;
}
inline void push_up(int o) {
    Seg &seg = st[o], &lc = st[LC(o)], &rc = st[RC(o)];
    seg.sum = mod1(lc.sum + rc.sum);
}
inline void update_mul(int o, int l, int r, int v) {
    Seg &seg = st[o];
    if (seg.r < l || r < seg.l)
        return;
    push_down(o);
    if (l <= seg.l && seg.r <= r) {
        seg.tm = v;
        seg.sum = (seg.sum * v) % mod;
        return;
    }
    update_mul(LC(o), l, r, v);
    update_mul(RC(o), l, r, v);
    push_up(o);
}
inline void update_add(int o, int l, int r, int v) {
    Seg &seg = st[o];
    if (seg.r < l || r < seg.l)
        return;
    push_down(o);
    if (l <= seg.l && seg.r <= r) {
        seg.ta = v;
        seg.sum = mod1(seg.sum + v * (seg.r - seg.l + 1));
        return;
    }
    update_add(LC(o), l, r, v);
    update_add(RC(o), l, r, v);
    push_up(o);
}
inline ll query(int o, int l, int r) {
    Seg &seg = st[o];
    if (seg.r < l || r < seg.l)
        return 0;
    push_down(o);
    if (l <= seg.l && seg.r <= r)
        return seg.sum;
    ll res = mod1(query(LC(o), l, r) + query(RC(o), l, r));
    return res;
}

int main() {
    int m, i, opt, l, r, x;
    scanf("%d%lld", &n, &mod);
    for (i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    build(1, 1, n);
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1) {
            scanf("%d", &x);
            update_mul(1, l, r, x % mod);
        } else if (opt == 2) {
            scanf("%d", &x);
            update_add(1, l, r, x % mod);
        } else
            printf("%lld\n", query(1, l, r));
    }

    return 0;
}
