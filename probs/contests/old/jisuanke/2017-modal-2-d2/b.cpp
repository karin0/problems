#include <cstdio>
#include <cmath>
#include <algorithm>

/*
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)
#define MID(x, y) (((x) + (y)) >> 1)
*/
#define LOWBIT(x) ((x) & (-(x)))

typedef long long ll;
const int MAXN = 100007;

struct Point {
    double x, y;
    int id;
};
Point sa[MAXN], sb[MAXN];
int pa[MAXN], pb[MAXN], ma[MAXN];
struct Line {
    ll k, b;
};
Line la, lb;
inline bool cmp(const Point &p, const Point &q) {
    return p.x < q.x;
}
inline Point cap(const Line &a, const Line &b, int id) {
    double y = (double)(a.b * b.k - b.b * a.k) / (b.k - a.k);
    return (Point){(y - a.b) / a.k, y, id};
}

int n;
ll ans;

/*
struct Seg {
    int l, r, v;
} st[MAXN * 4];
inline void build(int x, int l, int r) {
    Seg &seg = st[x];
    seg.l = l;
    seg.r = r;
    seg.v = 0;
    if (l == r) {
        return;
    }
    build(LC(x), l, MID(l, r));
    build(RC(x), MID(l, r) + 1, r);
}
inline int query(int x, int l, int r) {
    Seg &seg = st[x];
    if (r < seg.l || seg.r < l)
        return 0;
    if (l <= seg.l && seg.r <= r)
        return seg.v;
    return query(LC(x), l, r) + query(RC(x), l, r);
}
inline void update(int x, int l) {
    Seg &seg = st[x];
    if (l < seg.l || seg.r < l)
        return;
    if (seg.l == seg.r && seg.l == l) {
        seg.v += 1;
        return;
    }
    update(LC(x), l);
    update(RC(x), l);
    seg.v = st[LC(x)].v + st[RC(x)].v;
}
*/
int bit[MAXN];
inline void update(int x) {
    while (x <= n) {
        bit[x] += 1;
        x += LOWBIT(x);
    }
}
inline int query(int x) {
    int res = 0;
    while (x > 0) {
        res += bit[x];
        x -= LOWBIT(x);
    }
    return res;
}

int main() {
    ll k;
    int i;
    Line l;
    scanf("%lld%lld%lld%d", &k, &la.b, &lb.b, &n);
    la.k = lb.k = k;
    for (i = 1; i <= n; ++i) {
        scanf("%lld%lld", &l.k, &l.b);
        sa[i] = cap(l, la, i);
        sb[i] = cap(l, lb, i);
    }
    std::sort(sa + 1, sa + n + 1, cmp);
    std::sort(sb + 1, sb + n + 1, cmp);
    for (i = 1; i <= n; ++i) {
        pa[sa[i].id] = i;
        pb[sb[i].id] = i;
    }
    for (i = 1; i <= n; ++i)
        ma[pa[i]] = pb[i];

    for (i = 1; i <= n; ++i) {
        ans += query(n) - query(ma[i]);
        update(ma[i]);
    }

    printf("%lld\n", ans);
    return 0;
}
