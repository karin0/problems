#include <cstdio>
#include <cmath>
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)
#define MID(x, y) (((x) + (y)) >> 1)

const int MAXN = 100005;

namespace S {
    int n, a[MAXN];
    struct Seg {
        int l, r;
        long long sum;
        bool done, tag;
    } segs[MAXN << 2];
    
    inline void init(int x, int l, int r) {
        Seg &seg = segs[x];
        seg.l = l;
        seg.r = r;
        if (l == r) {
            seg.sum = a[l];
        } else {
            int mid = MID(l, r);
            init(LC(x), l, mid);
            init(RC(x), mid + 1, r);
            seg.sum = segs[LC(x)].sum + segs[RC(x)].sum;
        }
        seg.done = seg.sum <= 1;
    }
    inline void update(int x, int l, int r) {
        Seg &seg = segs[x];
        if (seg.done || seg.l > r || seg.r < l)
            return;
        if (l <= seg.l && seg.r <= r && seg.l == seg.r) {
            seg.sum = sqrt(seg.sum);
            if (seg.sum <= 1)
                seg.done = true;
            return;
        }
        update(LC(x), l, r);
        update(RC(x), l, r);
        seg.sum = segs[LC(x)].sum + segs[RC(x)].sum;
        if (segs[LC(x)].done && segs[RC(x)].done)
            seg.done = true;
    }
    inline long long query(int x, int l, int r) {
        Seg &seg = segs[x];
        if (seg.l > r || seg.r < l)
            return 0;
        if (l <= seg.l && seg.r <= r)
            return seg.sum;
        return query(LC(x), l, r) + query(RC(x), l, r);
    }

}

int main() {
    int m, opt, x, y, i;
    scanf("%d", &S::n);
    for (i = 1; i <= S::n; ++i)
        scanf("%d", &S::a[i]);
    S::init(1, 1, S::n);
    scanf("%d", &m);
    for (i = 0; i < m; ++i) {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            printf("%lld\n", S::query(1, x, y));
        else
            S::update(1, x, y);
    }

    return 0;
}
