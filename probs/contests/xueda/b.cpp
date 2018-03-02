#include <cstdio>
#include <algorithm>
#define LC(x) ((x) << 1)
#define RC(x) (((x) << 1) | 1)

typedef long long ll;
const int MAXN = 50005, MOD = 1000000007;
int n, mk = 10, a[MAXN];
ll comb[MAXN][11];
void make_comb() {
    static int i, j;
    comb[0][0] = 1;
    comb[1][0] = 1;
    comb[1][1] = 1;
    for (i = 2; i <= n; ++i) {
        comb[i][0] = 1;
        for (j = 1; j <= mk; ++j)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
    }
}
struct Seg {
    int l, r;
    ll ta, v[11];
    bool tn;
} st[MAXN << 2];
void build(int o, int l, int r) {
    Seg &seg = st[o];
    seg.l = l;
    seg.r = r;
    seg.ta = 0;
    seg.tn = false;
    seg.v[0] = 1;
    int i;
    if (l == r) {
        seg.v[1] = (a[l] + MOD) % MOD;
        for (i = 2; i <= 10; ++i)
            seg.v[i] = 0;
        return;
    }
    int mid = (l + r) >> 1, x;
    build(LC(o), l, mid);
    build(RC(o), mid + 1, r);
    Seg &lc = st[LC(o)], &rc = st[RC(o)];
    for (i = 1; i <= mk; ++i) {
        // lb = i + mid - r;
        seg.v[i] = 0;
        for (x = i + mid - r; x <= (mid - l + 1); ++x)
            seg.v[i] = (seg.v[i] + lc.v[x] * rc.v[i - x]) % MOD;
    }
}
ll cp[11];
void push_down(int o) {
    Seg &seg = st[o];
    if (seg.l == seg.r) {
        seg.ta = 0;
        seg.tn = false;
        return;
    }
    Seg &lc = st[LC(o)], &rc = st[RC(o)];
    int ub, i;
    if (seg.ta) {
        int j;
        lc.ta += seg.ta;
        rc.ta += seg.ta;
        int v = seg.ta;
        seg.ta = 0;
        int len = lc.r - lc.l + 1;
        ub = std::min(len, mk);
        for (i = 1; i <= ub; ++i) {
            cp[i] = (cp[i - 1] * v) % MOD;
            for (j = 1; j <= i; ++j)
                lc.v[i] = (lc.v[i] + cp[j] * lc.v[i - j] * comb[len - i + j][i]) % MOD;
        }
        len = rc.r - rc.l + 1;
        ub = std::min(len, mk);
        for (i = 1; i <= ub; ++i) {
            cp[i] = (cp[i - 1] * v) % MOD;
            for (j = 1; j <= i; ++j)
                rc.v[i] = (rc.v[i] + cp[j] * rc.v[i - j] * comb[len - i + j][i]) % MOD;
        }
    }
    if (seg.tn) {
        lc.tn = !lc.tn;
        rc.tn = !rc.tn;
        seg.tn = false;
        if (lc.ta != 0)
            lc.ta = (MOD - lc.ta) % MOD;
        ub = std::min(lc.r - lc.l + 1, mk);
        for (i = 1; i <= ub; ++i)
            if ((i & 1) && lc.v[i] != 0)
                lc.v[i] = (MOD - lc.v[i]) % MOD;
        if (rc.ta != 0)
            rc.ta = (MOD - rc.ta) % MOD;
        ub = std::min(rc.r - rc.l + 1, mk);
        for (i = 1; i <= ub; ++i)
            if ((i & 1) && rc.v[i] != 0)
                rc.v[i] = (MOD - rc.v[i]) % MOD;
    }
    
}
void add(int o, int l, int r, ll v) {
    Seg &seg = st[o];
    if (seg.l > r || seg.r < l)
        return;
    int len = seg.r - seg.l + 1;
    int ub = std::min(len, mk), i;
    if (l <= seg.l && seg.r <= r) {
        int j;
        seg.ta += v;
        for (i = 1; i <= ub; ++i) {
            cp[i] = (cp[i - 1] * v) % MOD;
            for (j = 1; j <= i; ++j)
                seg.v[i] = (seg.v[i] + cp[j] * seg.v[i - j] * comb[len - i + j][i]) % MOD;
        }
        return;
    }
    if (seg.tn || seg.ta)
        push_down(o);
    add(LC(o), l, r, v);
    add(RC(o), l, r, v);
    Seg &lc = st[LC(o)], &rc = st[RC(o)];
    int mid = (seg.l + seg.r) >> 1, x;
    for (i = 1; i <= ub; ++i) {
        // lb = i + mid - r;
        seg.v[i] = 0;
        for (x = i + mid - seg.r; x <= (mid - seg.l + 1); ++x)
            seg.v[i] = (seg.v[i] + lc.v[x] * rc.v[i - x]) % MOD;
    }
}
void neg(int o, int l, int r) {
    Seg &seg = st[o];
    if (seg.l > r || seg.r < l)
        return;
    int len = seg.r - seg.l + 1;
    int ub = std::min(len, mk), i;
    if (l <= seg.l && seg.r <= r) {
        if (seg.ta != 0)
            seg.ta = (MOD - seg.ta) % MOD;
        for (i = 1; i <= ub; ++i) {
            if ((i & 1) && seg.v[i] != 0)
            seg.v[i] = (MOD - seg.v[i]) % MOD;
        }
        seg.tn = !seg.tn;
        return;
    }
    if (seg.tn || seg.ta)
        push_down(o);
    neg(LC(o), l, r);
    neg(RC(o), l, r);
    Seg &lc = st[LC(o)], &rc = st[RC(o)];
    int mid = (seg.l + seg.r) >> 1, x;
    for (i = 1; i <= ub; ++i) {
        seg.v[i] = 0;
        for (x = i + mid - seg.r; x <= (mid - seg.l + 1); ++x)
            seg.v[i] = (seg.v[i] + lc.v[x] * rc.v[i - x]) % MOD;
    }
}
ll query(int o, int l, int r, int v) {
    Seg &seg = st[o];
    if (seg.l > r || seg.r < l)
        return 0;
    if (l <= seg.l && seg.r <= r)
        return (seg.v[v] + MOD) % MOD;
    if (seg.tn || seg.ta)
        push_down(o);
    return ((query(LC(o), l, r, v) + query(RC(o), l, r, v)) % MOD + MOD) % MOD;
}
int main() {
    static int m, i, l, r, v, opt;
    cp[0] = 1;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", a + i);
    make_comb();
    build(1, 1, n);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 2)
            neg(1, l, r);
        else {
            scanf("%d", &v);
            if (opt == 1)
                add(1, l, r, v);
            else
                printf("%lld\n", (v == 0) ? 0 : query(1, l, r, v));
        }
    }
    
    return 0;
}
