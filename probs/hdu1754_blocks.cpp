#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 200005;
const int MAXB = 1000;
const int INF = 2147483647;

namespace Blocks {
    int n, bsize, a[MAXN], b[MAXB];

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
        int bi;
        bsize = ceil(sqrt(n));
        std::fill(b + 1, b + bpos(n) + 1, -INF);
        for (int i = 1; i <= n; ++i) {
            bi = bpos(i);
            b[bi] = std::max(b[bi], a[i]);
        }
    }
    inline int query(int x, int y) {
        int bx = bpos(x), by = bpos(y), res = -INF, i;
        if (bx == by)
            for (i = x; i <= y; ++i)
                res = std::max(res, a[i]);
        else {
            for (i = x; bpos(i) == bx; ++i)
                res = std::max(res, a[i]);
            for (i = bl(by); i <= y; ++i)
                res = std::max(res, a[i]);
            for (i = bx + 1; i < by; ++i)
                res = std::max(res, b[i]);
        }
        return res;
    }
    inline void update(int x, int v) {
        int bx = bpos(x);
        if (b[bx] == a[x] && v < a[x]) {
            b[bx] = -INF;
            a[x] = v;
            int r = br(bx);
            for (int i = bl(bx); i <= r; ++i)
                b[bx] = std::max(b[bx], a[i]);
        } else {
            b[bx] = std::max(b[bx], v);
            a[x] = v;
        }
    }
}

int main() {
    int m, x, y, i;
    char opt[3];
    while (scanf("%d%d", &Blocks::n, &m) == 2) {
        for (i = 1; i <= Blocks::n; ++i) {
            scanf("%d", Blocks::a + i);
        }
        Blocks::init();
        while (m--) {
            scanf("%s%d%d", opt, &x, &y);
            if (opt[0] == 'Q')
                printf("%d\n", Blocks::query(x, y));
            else
                Blocks::update(x, y);
        }
    }

    return 0;
}
