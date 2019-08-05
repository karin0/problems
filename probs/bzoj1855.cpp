#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

const int N = 2005;
int n, mp, w, ap[N], bp[N], as[N], bs[N];
inline void upd(int &x, int v) {
    x = std::max(x, v);
}
struct Item {
    int i, v;
};
struct MonoQueue {
    Item q[N], *hd, *tl;
    void init() {
        hd = q + 1, tl = q;
    }
    int top(int a, int b) {
        while (tl - hd + 1 > 0 && (hd->i < a || hd->i > b))
            ++hd;
        return hd->v;
    }
    void push(int i, int v) {
        while (tl - hd + 1 > 0 && tl->v < v)
            --tl;
        *(++tl) = (Item){i, v};
    }
} q;
void read(int &x) {
    static char c;
    for (c = 0; !isdigit(c); c = getchar());
    for (x = 0; isdigit(c); x = x * 10 + (c - '0'), c = getchar());
}
int main() {
    static int i, j;
    static int f[N][N];
    read(n); read(mp); read(w);
    for (i = 1; i <= n; ++i)
        read(ap[i]), read(bp[i]), read(as[i]), read(bs[i]);
    for (i = 0; i <= n; ++i)
       for (j = 0; j <= mp; ++j)
           f[i][j] = -0x7f7f7f7f;
    for (i = 1; i <= n; ++i) {
        for (j = 0; j <= mp; ++j)
            f[i][j] = f[i - 1][j];
        for (j = 0; j <= as[i]; ++j)
            upd(f[i][j], -ap[i] * j); // ***
        if (i - w - 1 <= 0)
            continue;
        q.init();
        for (j = 0; j <= mp; ++j)  { //
            q.push(j, f[i - w - 1][j] + ap[i] * j);
            upd(f[i][j], q.top(j - as[i], j) - ap[i] * j); // to buy
        }
        q.init();
        for (j = mp; j >= 0; --j)  { //
            q.push(j, f[i - w - 1][j] + bp[i] * j);
            upd(f[i][j], q.top(j, j + bs[i]) - bp[i] * j); // to sell
        }
    }
    printf("%d\n", f[n][0]);
    return 0;
}
