#include <cstdio>
#include <algorithm>
#define LC(o) ((o) << 1)
#define RC(o) (((o) << 1) | 1)
using std::max;
using std::min;

// typedef long long ll;
const int MAXN = 100005;
int n;
int a[3][MAXN], val[MAXN * 3], vcnt;

inline void upd(int &x, const int v) {
    x = max(x, v);
}
struct Seg {
    int v, l, r;
};
inline int lowbit(int x) {
    return x & -x;
}
struct Bit {
    int c[MAXN * 3];
    void update(int o, const int v) {
        for (; o < vcnt; o += lowbit(o))
            upd(c[o], v);
    }
    int query(int o) {
        static int res;
        for (res = 0; o >= 1; o -= lowbit(o))
            upd(res, c[o]);
        return res;
    }
    void init() {
        static int i;
        for (i = 1; i < vcnt; ++i)
            c[i] = 0;
    }
} bit[2][4];

int main() {
    static int i, k, ans = 1, f[4];
    scanf("%d", &n);
    for (k = 0; k <= 2; ++k)
        for (i = 1; i <= n; ++i)
            scanf("%d", a[k] + i), val[++vcnt] = a[k][i];
    std::sort(val + 1, val + vcnt + 1);
    vcnt = std::unique(val + 1, val + vcnt + 1) - val;
    for (k = 0; k <= 2; ++k)
        for (i = 1; i <= n; ++i)
            a[k][i] = std::lower_bound(val + 1, val + vcnt, a[k][i]) - val;
    for (k = 0; k <= 2; ++k) {
        // bit[0][k].init();
        // bit[1][k].init();
        bit[0][k].update(vcnt - a[k][1], 1);
        bit[1][k].update(a[k][1], 1);
    }
    // bit[0][3].init();
    // bit[1][3].init();
    bit[0][3].update(vcnt - a[2][1], 1);
    bit[1][3].update(a[2][1], 1);
    for (i = 2; i <= n; ++i) {
        for (k = 0; k <= 3; ++k)
            f[k] = 1;
        for (k = 0; k <= 3; ++k) {
            upd(f[0], bit[1][k].query(a[0][i]) + 1);
            upd(f[1], bit[0][k].query(vcnt - a[1][i]) + 1);
        }
        for (k = 0; k <= 1; ++k) {
            upd(f[2], bit[0][k].query(vcnt - a[2][i]) + 1);
            upd(f[3], bit[1][k].query(a[2][i]) + 1);
        }
        upd(f[2], bit[0][2].query(vcnt - a[2][i]) + 1);
        upd(f[3], bit[1][3].query(a[2][i]) + 1);
        for (k = 0; k <= 2; ++k) {
            bit[0][k].update(vcnt - a[k][i], f[k]);
            bit[1][k].update(a[k][i], f[k]);
        }
        bit[0][3].update(vcnt - a[2][i], f[3]);
        bit[1][3].update(a[2][i], f[3]);
        upd(ans, max(max(f[0], f[1]), max(f[2], f[3])));
    } 
    printf("%d\n", ans);
    return 0;
}
