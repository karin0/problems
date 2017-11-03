#include <cstdio>
#include <algorithm>
#define LC(o) ((o) << 1)
#define RC(o) (((o) << 1) | 1)
using std::max;
using std::min;

// typedef long long ll;
const int MAXN = 100055;
int n;
int a[3][MAXN], f[4][MAXN], val[MAXN * 3], vcnt;

inline void upd(int &x, const int v) {
    x = max(x, v);
}
struct Seg {
    int v, l, r;    
};
struct SegTree {
    Seg st[MAXN * 3 * 4];
    int lind[MAXN * 3];
    void build(int o, int l, int r) {
        Seg &seg = st[o];
        seg.v = 0;
        seg.l = l;
        seg.r = r;
        int mid = (l + r) >> 1;
        if (l == r)
            lind[l] = o;
        else
            build(LC(o), l, mid), build(RC(o), mid + 1, r);
    }
    void update(int o, int x) {
        for(o = lind[o]; o; o >>= 1)
            upd(st[o].v, x);
    }
    /*
    void update(int o, int x, int v) {
        Seg &seg = st[o];
        upd(seg.v, v);
        if (seg.r < x || seg.l > x)
            return;
        if (seg.l == x && seg.r == x)
            return;
        int mid = (seg.l + seg.r) >> 1;
        if (mid >= x)
            update(LC(o), x, v);
        else
            update(RC(o), x, v);
    }*/
    int query(int o, int l, int r) {
        Seg &seg = st[o];
        if (seg.l > r || seg.r < l)
            return 0;
        if (l <= seg.l && seg.r <= r)
            return seg.v;
        return max(query(LC(o), l, r), query(RC(o), l, r));
    }
} segt[4];

int main() {
    static int i, k, ans = 1;
    scanf("%d", &n);
    for (k = 0; k <= 2; ++k)
        for (i = 1; i <= n; ++i)
            scanf("%d", a[k] + i), val[++vcnt] = a[k][i];
    std::sort(val + 1, val + vcnt + 1);
    vcnt = std::unique(val + 1, val + vcnt + 1) - val - 1;
    for (k = 0; k <= 2; ++k)
        for (i = 1; i <= n; ++i)
            a[k][i] = std::lower_bound(val + 1, val + vcnt + 1, a[k][i]) - val;
    for (k = 0; k <= 3; ++k)
        segt[k].build(1, 1, vcnt);
    for (k = 0; k <= 3; ++k)
        f[k][1] = 1;
    for (k = 0; k <= 3; ++k)
        segt[k].build(1, 1, vcnt);
    for (k = 0; k <= 2; ++k)
        segt[k].update(a[k][1], 1);
    segt[3].update(a[2][1], 1);
    for (i = 2; i <= n; ++i) {
        for (k = 0; k <= 3; ++k)
            f[k][i] = 1;
        for (k = 0; k <= 3; ++k) {
            upd(f[0][i], segt[k].query(1, 1, a[0][i]) + 1);
            upd(f[1][i], segt[k].query(1, a[1][i], vcnt) + 1);
        }
        for (k = 0; k <= 1; ++k) {
            upd(f[2][i], segt[k].query(1, a[2][i], vcnt) + 1);
            upd(f[3][i], segt[k].query(1, 1, a[2][i]) + 1);
        }
        upd(f[2][i], segt[2].query(1, a[2][i], vcnt) + 1);
        upd(f[3][i], segt[3].query(1, 1, a[2][i]) + 1);
        for (k = 0; k <= 2; ++k)
            segt[k].update(a[k][i], f[k][i]);
        segt[3].update(a[2][i], f[3][i]);
        upd(ans, max(max(f[0][i], f[1][i]), max(f[2][i], f[3][i])));
    } 
    printf("%d\n", ans);
    return 0;
}
