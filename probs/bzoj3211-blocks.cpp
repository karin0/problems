#include <cstdio>
#include <cmath>

const int MAXN = 100005;
const int MAXB = 1000;

namespace S {
    int n, bsize, a[MAXN];
    struct Block {
        long long old_sum;
        int done;
    };
    static Block blocks[MAXB];
    
    inline int bmap(int x) {
        return (x - 1) / bsize + 1;
    }
    inline int bl(int x) {
        return (x - 1) * bsize + 1;
    }
    inline int br(int x) {
        return x * bsize;
    }
    inline void init() {
        bsize = ceil(sqrt(n));
        for (int i = 1; i <= n; ++i)
            blocks[bmap(i)].old_sum += a[i];
    }
    inline void update(int x, int y) {
        int bx = bmap(x), by = bmap(y), i, old;
        if (bx == by) {
            for (i = x; i <= y; ++i) {
                old = a[i];
                a[i] = sqrt(a[i]);
                blocks[bx].old_sum += a[i] - old;
            }
        } else {
            bool done;
            int r = br(bx), j;
            for (i = x; i <= r; ++i) {
                old = a[i];
                a[i] = sqrt(a[i]);
                blocks[bx].old_sum += a[i] - old;
            }
            for (i = bl(by); i <= y; ++i) {
                old = a[i];
                a[i] = sqrt(a[i]);
                blocks[by].old_sum += a[i] - old;
            }
            for (i = bx + 1; i < by; ++i) {
                Block &b = blocks[i];
                if (b.done < bsize) {
                    done = true;
                    r = br(i);
                    for (j = bl(i) + b.done; j <= r; ++j) { // ***
                        if (a[j] > 1) {
                            old = a[j];
                            a[j] = sqrt(a[j]);
                            b.old_sum += a[j] - old;
                            if (done && a[j] > 1)
                                done = false, b.done = j - bl(i);
                        }
                    }
                    if (done)
                        b.done = bsize;
                }
            }
        }
    }
    inline long long query(int x, int y) {
        int bx = bmap(x), by = bmap(y), i;
        long long res = 0;
        if (bx == by) {
            for (i = x; i <= y; ++i)
                res += a[i];
        } else {
            int r = br(bx);
            for (i = x; i <= r; ++i)
                res += a[i];
            for (i = bl(by); i <= y; ++i)
                res += a[i];
            for (i = bx + 1; i < by; ++i) {
                res += blocks[i].old_sum;
            }
        }
        return res;
    }
}

int main() {
    int m, opt, x, y, i;
    scanf("%d", &S::n);
    for (i = 1; i <= S::n; ++i)
        scanf("%d", &S::a[i]);
    S::init();
    scanf("%d", &m);
    for (i = 0; i < m; ++i) {
        scanf("%d%d%d", &opt, &x, &y);
        if (opt == 1)
            printf("%lld\n", S::query(x, y));
        else
            S::update(x, y);
    }

    return 0;
}
