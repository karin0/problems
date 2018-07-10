// Taihen da.
#include <cstdio>
#define MAXN 100100
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)
#define MID(x, y) ((x) + (((y) - (x)) >> 1))
#define LONG(x) ((rb[(x)] - lb[(x)] + 1) % mod)
int n;
long long mod;
long long a[MAXN], val[MAXN * 4], tag[MAXN * 4][2];
int lb[MAXN * 4], rb[MAXN * 4]; 

int s_l, s_r, s_v;
// Caution:
// - 4 * MAXN
// - if (l == r) val[u] = a[l];
//                        ^
// - Range including.

void build(int u, int l, int r) {
    lb[u] = l;
    rb[u] = r;
    //printf("<%d, %d, %d>\n", u, lb[u], rb[u]);
    tag[u][0] = 1;
    if (l == r)
        val[u] = a[l] % mod;  // Caution
    else {
        build(LC(u), l, MID(l, r));
        build(RC(u), MID(l, r) + 1, r);
        val[u] = (val[LC(u)] + val[RC(u)]) % mod;
    }
}
inline void push_down(int u) {
    long long &v0 = tag[u][0], &v1 = tag[u][1];
    (val[LC(u)] += v1 * LONG(LC(u))) %= mod;
    (val[RC(u)] += v1 * LONG(RC(u))) %= mod;
    (val[LC(u)] *= v0) %= mod;
    (val[RC(u)] *= v0) %= mod;
    (tag[LC(u)][1] += v1) %= mod;
    (tag[RC(u)][1] += v1) %= mod;
    (tag[LC(u)][1] *= v0) %= mod;
    (tag[RC(u)][1] *= v0) %= mod;
    (tag[LC(u)][0] *= v0) %= mod;
    (tag[RC(u)][0] *= v0) %= mod;
    v0 = 1;
    v1 = 0;
}
void update0(int u) {
    if (rb[u] < s_l || s_r < lb[u]) return;
    if (s_l <= lb[u] && rb[u] <= s_r) {
        (val[u] *= s_v) %= mod;
        (tag[u][0] *= s_v) %= mod;
        (tag[u][1] *= s_v) %= mod;
    } else {
        if (tag[u][0] != 1 || tag[u][1] != 0) push_down(u);
        update0(LC(u));
        update0(RC(u));
        val[u] = (val[LC(u)] + val[RC(u)]) % mod;
    }
}
void update1(int u) {
    if (rb[u] < s_l || s_r < lb[u]) return;
    if (s_l <= lb[u] && rb[u] <= s_r) {
        (val[u] += s_v * LONG(u)) %= mod;
        (tag[u][1] += s_v) %= mod;
    } else {
        if (tag[u][0] != 1 || tag[u][1] != 0) push_down(u);
        update1(LC(u));
        update1(RC(u));
        val[u] = (val[LC(u)] + val[RC(u)]) % mod;
    }
}
long long query(int u) {
    if (rb[u] < s_l || s_r < lb[u]) return 0;
    if (s_l <= lb[u] && rb[u] <= s_r) {
        return val[u];
    } else {
        push_down(u);
        return (query(LC(u)) + query(RC(u))) % mod;
    }
}
inline void init() {
    build(1, 1, n);
    // for (register int i = 1; i <= n; ++i)
    //     tag[i][0] = 1;
}

int main() {
    register int q;
    scanf("%d%d%lld", &n, &q, &mod);
    for (register int i = 1; i <= n; ++i) {
        scanf("%lld", a + i);
    }
    init();
    int opt, x, y;
    long long k;
    while (q--) {
        scanf("%d%d%d", &opt, &x, &y);
        s_l = x;
        s_r = y;
        if (opt == 3) printf("%lld\n", query(1));
        else {
            scanf("%lld", &k);
            s_v = k % mod;
            if (opt - 1) update1(1); // 0 - mul, 1 - add
            else update0(1);
        }
    }
    return 0;
}
