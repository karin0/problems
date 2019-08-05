#include <cstdio>
#include <algorithm>

#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)
#define MID(x, y) (((x) + (y)) >> 1)

const int MAXN = 1e5 + 5;

int on, n, a[MAXN], b[MAXN];

struct Seg {
    int l, r, v;
} st[MAXN * 4];
inline void build(int x, int l, int r) {
    Seg &seg = st[x];
    seg.l = l;
    seg.r = r;
    if (l == r) {
        seg.v = std::min(a[l], b[l]);
        seg.l = l;
        seg.r = r;
        return;
    }
    build(LC(x), l, MID(l, r));
    build(RC(x), MID(l, r) + 1, r);
    seg.v = st[LC(x)].v + st[RC(x)].v;
}
inline int query(int x, int l, int r) {
    Seg &seg = st[x];
    if (r < seg.l || seg.r < l)
        return 0;
    if (l <= seg.l && seg.r <= r)
        return seg.v;
    return query(LC(x), l, r) + query(RC(x), l, r);
}
inline void update(int x, int l, int v) {
    Seg &seg = st[x];
    if (l < seg.l || seg.r < l)
        return;
    if (seg.l == seg.r && seg.l == l) {
        seg.v = v;
        return;
    }
    update(LC(x), l, v);
    update(RC(x), l, v);
    seg.v = st[LC(x)].v + st[RC(x)].v;
}

int main() {
    int m, i, j, opt, x, y;
    scanf("%d%d", &on, &m);
    n = on - 1;
    for (i = 1; i < on; ++i)
        scanf("%d", a + i);
    for (i = 1; i < on; ++i)
        scanf("%d", b + i);
    for (i = 1; i <= on; ++i)
        scanf("%d", &j); // all 0
    build(1, 1, n);
    while (m--) {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1) {
            printf("%d\n", query(1, x, y - 1));
        } else if (opt == 2) {
            if (std::min(y, b[x]) != std::min(a[x], b[x]))
                update(1, x, std::min(y, b[x]));
            a[x] = y;
        } else if (opt == 3) {
            if (std::min(a[x], y) != std::min(a[x], b[x]))
                update(1, x, std::min(a[x], y));
            b[x] = y;
        }
    }

    return 0;
}
