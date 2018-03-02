#include <cstdio>
#define LC(r) ((r) << 1)
#define RC(r) (((r) << 1) | 1)
#define MID(l, r) ((l + r) >> 1)
#define LEN(r) (rb[r] - lb[r] + 1)
typedef long long LL;
const int MAXN = 1e5 + 10;
const int MAXK = 10;
const LL MOD = 1e9 + 7;
const LL NOPE = 1e12;

int n, raw[MAXN][10];
LL qpow(LL x, LL p) {
    LL res = 1;
    for (; p; p >>= 1, x = (x * x) % MOD)
        if (p & 1)
            res = (res * x) % MOD;
    return res;
}
LL c[MAXK + 3][MAXK + 3];
inline void make_c() {
    for (int i = 1; i <= MAXK; ++i) {
        for (int j = 0; j <= MAXK; ++j) {
            if (i == j || j == 0)
                c[i][j] = 1;
            else
                c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % MOD;
        }
    }
}
LL delta(int l, int r, int d, int p); 
struct SegTree {
    int p, lb[MAXN << 2], rb[MAXN << 2];
    LL val[MAXN << 2], tagb[MAXN << 2], tagt[MAXN << 2];
    bool no_push;
    inline void build(int k, int l, int r) {
        lb[k] = l, rb[k] = r, tagb[k] = 0, tagt[k] = NOPE; // f
        if (l == r) {
            if (p > 1)
                raw[l][p - 1] = (raw[l][p - 2] * raw[l][0]) % MOD;
            val[k] = raw[l][p - 1];
        } else {
            build(LC(k), l, MID(l, r));
            build(RC(k), MID(l, r) + 1, r);
            val[k] = (val[LC(k)] + val[RC(k)]) % MOD;
        }
    } // 外部定义 p 并调用 init()
    inline void push_down(int k) { // 先传修改到
        if (tagt[k] != NOPE) {
            tagt[LC(k)] = tagt[RC(k)] = tagt[k];
            LL qp = qpow(tagt[k], p);
            val[LC(k)] = (qp * LEN(LC(k))) % MOD;
            val[RC(k)] = (qp * LEN(RC(k))) % MOD;
            tagt[k] = NOPE;
        }
        if (tagb[k] != 0) {
            tagb[LC(k)] = (tagb[LC(k)] + tagb[k]) % MOD;
            tagb[RC(k)] = (tagb[RC(k)] + tagb[k]) % MOD;
            no_push = true;
            val[LC(k)] = (val[LC(k)] + delta(lb[LC(k)], rb[LC(k)], tagb[k], p)) % MOD;
            val[RC(k)] = (val[RC(k)] + delta(lb[RC(k)], rb[RC(k)], tagb[k], p)) % MOD;
            no_push = false;
            tagb[k] = 0;
        }
    }
    inline LL query(int k, int l, int r) {
        if (r < lb[k] || rb[k] < l)
            return 0;
        if (l <= lb[k] && rb[k] <= r)
            return val[k];
        if (!no_push)
            push_down(k);
        return (query(LC(k), l, r) + query(RC(k), l, r)) % MOD;
    }
    inline void update_to(int k, int l, int r, int x) {
        if (r < lb[k] || rb[k] < l)
            return;
        if (l <= lb[k] && rb[k] <= r) {
            val[k] = (qpow(x, p) * LEN(k)) % MOD;
            tagb[k] = 0;
            tagt[k] = x;
        }
        tagb[k] = 0;
        push_down(k);
        update_to(LC(k), l, r, x);
        update_to(RC(k), l, r, x);
        val[k] = (val[LC(k)] + val[RC(k)]) % MOD;
    }
    inline void update_by(int k, int l, int r, int x) {
        if (r < lb[k] || rb[k] < l)
            return;
        if (l <= lb[k] && rb[k] <= r) {
            push_down(k);
            no_push = true;
            val[k] = (val[k] + delta(lb[k], rb[k], x, p)) % MOD;
            no_push = false;
            tagb[k] = (tagb[k] + x) % MOD;
        }
        push_down(k);
        update_by(LC(k), l, r, x);
        update_by(RC(k), l, r, x);
        val[k] = (val[LC(k)] + val[RC(k)]) % MOD;
    }

} sts[10];
LL delta(int l, int r, int d, int p) {
    printf("[%d %d %d %d]", l, r, d, p);
    LL res = 0;
    for (int i = 0; i <= p; ++i) {
        res = (res + (((c[p][i] * qpow(d, i) - ((i == 0) ? 1 : 0)) % MOD) * (p == i ? (r - l + 1) : sts[p - i - 1].query(1, l, r))) % MOD) % MOD;
    }
    return res;
}


int main() {
    int q, i, opt, l, r, x;
    scanf("%d%d", &n, &q);
    for (i = 1; i <= n; ++i)
        scanf("%d", &raw[i][0]); // pow 1
    make_c();
    for (i = 0; i < MAXK; ++i) {
        sts[i].p = i + 1;
        sts[i].build(1, 1, n);
        sts[i].no_push = false;
    }
    while (q--) {
        scanf("%d%d%d%d", &opt, &l, &r, &x);
        if (opt == 1) 
            for (i = 0; i < MAXK; ++i)
                sts[i].update_by(1, l, r, x);
        else if (opt == 2)
            for (i = 0; i < MAXK; ++i)
                sts[i].update_to(1, l, r, x);
        else
            printf("%lld\n", x ? sts[x - 1].query(1, l, r) : (r - l + 1));

    
    }
    return 0;
}
