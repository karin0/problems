#include <cstdio>
#include <cmath>

const int MAXN = 100005;
const int MAXB = 1000;

namespace Blocks {
    int n, bsize;
    long long a[MAXN], b[MAXB], tag[MAXB];

    inline int bpos(int x) {
        return (x - 1) / bsize + 1;
    }
    inline int bl(int bx) {
        return (bx - 1) * bsize + 1;
    }
    inline int br(int bx) {
        return bx * bsize;
    }
    inline void init() { // 用 n, a[] 初始化
        bsize = ceil(sqrt(n));
        // std::fill(b + 1, b + bpos(n) + 1, 0);
        // std::fill(tag + 1, tag + bpos(n) + 1, 0);
        for (int i = 1; i <= n; ++i)
            b[bpos(i)] += a[i];
    }
    inline long long query(int x, int y) {
        int bx = bpos(x), by = bpos(y), i;
        long long res = 0;
        if (bx == by)
            for (i = x; i <= y; ++i)
                res += a[i];
        else {
            for (i = x; bpos(i) == bx; ++i)
                res += a[i];
            for (i = bl(by); i <= y; ++i)
                res += a[i];
            res += tag[bx] * (br(bx) - x + 1) + tag[by] * (y - bl(by) + 1);
            for (i = bx + 1; i < by; ++i)
                res += b[i] + tag[i] * bsize;;
        }
        return res;
    }
    inline void update(int x, int y, long long v) {
        int bx = bpos(x), by = bpos(y), i;
        if (bx == by) {
            b[bx] += v * (y - x + 1);
            for (i = x; i <= y; ++i)
                a[i] += v;
        } else {
            for (i = x; bpos(i) == bx; ++i)
                a[i] += v;
            for (i = bl(by); i <= y; ++i)
                a[i] += v;
            b[bx] += v * (br(bx) - x + 1);
            b[by] += v * (y - bl(by) + 1);
            for (i = bx + 1; i < by; ++i)
                tag[i] += v;
        }
    }
}

int main() {
    int m, x, y, opt, i;
    long long v;
    scanf("%d%d", &Blocks::n, &m);
    for (i = 1; i <= Blocks::n; ++i) {
        scanf("%lld", Blocks::a + i);
    }
    Blocks::init();
    while (m--) {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 2)
            printf("%lld\n", Blocks::query(x, y));
        else {
            scanf("%lld", &v);
            Blocks::update(x, y, v);
        }
    }

    return 0;
}
