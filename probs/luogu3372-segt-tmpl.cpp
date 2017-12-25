#include <cstdio>

typedef long long ll;
const int MAXN = 100005;

int n;
ll a[MAXN];
struct Seg {
    int l, r;
    ll v, tag;
    Seg *lc, *rc;
} *rt, pool[MAXN << 2];
int cnt;
Seg* newnode(int l, int r) {
    return pool + (cnt++);
}
void build(Seg *o, int l, int r) {
    Seg &seg = *o;
    seg.l = l;
    seg.r = r;
    if (l == r)
        seg.v = a[l];
    else {
        int mid = (l + r) >> 1;
        seg.lc = newnode();
        seg.rc = newnode();
        build(seg.lc, l, mid);
        build(seg.rc, mid + 1, r);
        seg.v = seg.lc->v + seg.rc->v;
    }
}
inline int len(Seg &seg) {
    return seg.r - seg.l + 1;
}
inline void push_down(Seg *o) {
    static ll t;
    Seg &seg = *o, &slc = *(o->lc), &src = *(o->rc);
    t = seg.tag;
    seg.tag = 0;
    slc.v += t * len(slc);
    slc.tag += t;
    src.v += t * len(src);
    src.tag += t;
}
void update(Seg *o, int l, int r, ll v) {
    Seg &seg = *o;
    if (l <= seg.l && seg.r <= r) {
        seg.v += v * len(seg);
        seg.tag += v;
        return;
    }
    if (seg.tag)
        push_down(o); // !!!
    int mid = (seg.l + seg.r) >> 1;
    if (l <= mid)
        update(seg.lc, l, r, v);
    if (r > mid)
        update(seg.rc, l, r, v);
    seg.v = seg.lc->v + seg.rc->v; // !!!
}
ll query(Seg *o, int l, int r) {
    Seg &seg = *o;
    if (l <= seg.l && seg.r <= r)
        return seg.v;
    if (seg.tag)
        push_down(o);
    int mid = (seg.l + seg.r) >> 1;
    ll res = 0;
    if (l <= mid)
        res = query(seg.lc, l, r);
    if (r > mid)
        res += query(seg.rc, l, r);
    return res;
}

int main() {
    static int m, i, opt, l, r;
    static ll v;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    rt = newnode();
    build(rt, 1, n);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 1)
            scanf("%lld", &v), update(rt, l, r, v);
        else
            printf("%lld\n", query(rt, l, r));
    }

    return 0;
}
