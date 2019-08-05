#include <cstdio>
#define LC(o) ((o) << 1)
#define RC(o) (((o) << 1) | 1)

typedef long long ll;
const int MAXN = 100005;

int n;
ll a[MAXN];
struct Seg {
    int l, r;
    ll v, tag;
} st[MAXN << 2];
void build(int o, int l, int r) {
    Seg &seg = st[o];
    seg.l = l;
    seg.r = r;
    // seg.v = 0;
    // seg.tag = 0;
    if (l == r)
        seg.v = a[l];
    else {
        int mid = (l + r) >> 1;
        build(LC(o), l, mid);
        build(RC(o), mid + 1, r);
        seg.v = st[LC(o)].v + st[RC(o)].v;
    }
}
inline int len(const Seg &seg) {
    return seg.r - seg.l + 1;
}
inline void push_down(int o) {
    static ll t;
    Seg &seg = st[o], &slc = st[LC(o)], &src = st[RC(o)];
    t = seg.tag;
    seg.tag = 0;
    slc.v += t * len(slc);
    slc.tag += t;
    src.v += t * len(src);
    src.tag += t;
}
void update(int o, int l, int r, ll v) {
    Seg &seg = st[o];
    if (l <= seg.l && seg.r <= r) {
        seg.v += v * len(seg);
        seg.tag += v;
        return;
    }
    if (seg.tag)
        push_down(o); // !!!
    int mid = (seg.l + seg.r) >> 1;
    if (l <= mid)
        update(LC(o), l, r, v);
    if (r > mid)
        update(RC(o), l, r, v);
    seg.v = st[LC(o)].v + st[RC(o)].v; // !!!
}
ll query(int o, int l, int r) {
    Seg &seg = st[o];
    if (l <= seg.l && seg.r <= r)
        return seg.v;
    if (seg.tag)
        push_down(o);
    int mid = (seg.l + seg.r) >> 1;
    ll res = 0;
    if (l <= mid)
        res = query(LC(o), l, r);
    if (r > mid)
        res += query(RC(o), l, r);
    return res;
}

int main() {
    static int m, i, opt, l, r;
    static ll v;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    build(1, 1, n);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
            scanf("%lld", &v), update(1, l, r, v);
        else
            printf("%lld\n", query(1, l, r));
    }

    return 0;
