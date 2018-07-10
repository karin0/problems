#include <cstdio>
#include <cmath>
#include <algorithm>

const int MAXN = 200100;

namespace S {
    int n, a[MAXN], bsize, next[MAXN], w[MAXN];

    inline int bmap(int x) {
        return (x - 1) / bsize + 1;
    }
    inline int bl(int x) {
        return (x - 1) * bsize + 1;
    }
    inline int br(int x) {
        return std::min(x * bsize, n);
    }
    inline void init() {
        bsize = ceil(sqrt(n));
        int r = bmap(n), ll, rr, bi, i;
        for (bi = 1; bi <= r; ++bi) {
            ll = bl(bi);
            rr = br(bi);
            for (i = rr; i >= ll; --i) {
                if (a[i] > rr)
                    next[i] = a[i], w[i] = 1;
                else
                    next[i] = next[a[i]], w[i] = w[a[i]] + 1; // 因为保证了 a[i] > i
            }
        }
    }
    inline void update(int x, int v) {
        int bx = bmap(x), i;
        a[x] = v;
        int ll = bl(bx), rr = br(bx);
        for (i = x; i >= ll; --i) {
            if (a[i] > rr)
                next[i] = a[i], w[i] = 1;
            else
                next[i] = next[a[i]], w[i] = w[a[i]] + 1;
        }
    }
    inline int query(int x) {
        int res = 0;
        for (; x <= n; res += w[x], x = next[x]);
        return res;
    }

}

int main() {
    // freopen("bzoj_2002.in", "r", stdin);
    // freopen("bzoj_2002.out", "w", stdout);
    int m, opt, x, y, i;
    scanf("%d", &S::n);
    for (i = 1; i <= S::n; ++i) {
        scanf("%d", &x);
        S::a[i] = i + x; // 直接存储后继位置
    }
    S::init();
    scanf("%d", &m);
    for (i = 0; i < m; ++i) {
        scanf("%d%d", &opt, &x);
        x += 1; // 0 ~ n - 1 => 1 ~ n
        if (opt == 1)
            printf("%d\n", S::query(x));
        else {
            scanf("%d", &y);
            S::update(x, x + y);
        }
    }
    return 0;
}
