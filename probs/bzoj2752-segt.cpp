#include <cstdio>

typedef long long ll;
int n;
ll ssq[100005];
struct Triple {
    ll x[3];
    Triple() {
        x[0] = x[1] = x[2] = 0;
    }
    Triple(ll a, ll b, ll c) {
        x[0] = a, x[1] = b, x[2] = c;
    }
} zeros;
Triple operator + (const Triple &a, const Triple &b) {
    return Triple(a.x[0] + b.x[0], a.x[1] + b.x[1], a.x[2] + b.x[2]);
}
struct SegT {
    int l, r, len;
    int tag;
    Triple s;
    SegT *lc, *rc;
    SegT(int _l, int _r, SegT *_lc, SegT *_rc) : l(_l), r(_r), len(_r - _l + 1), lc(_lc), rc(_rc) {}

    void maintain() {
        s = lc->s + rc->s;
    }
    void add(int x) {
        s.x[0] += (ll)len * x;
        s.x[1] += (ll)(l + r) * len / 2 * x;
        // s.x[2] += (ll)((ll)r * (r + 1) * (2 * r + 1) - (ll)(l - 1) * l * (2 * l - 1)) / 6 * x;
        s.x[2] += (ssq[r] - ssq[l - 1]) * x;
        tag += x;
    }
    void push_down() {
        if (tag && lc)
            lc->add(tag), rc->add(tag), tag = 0;
    }
    void update(int ql, int qr, int x) {
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr) {
            add(x);
            return;
        }
        push_down();
        lc->update(ql, qr, x);
        rc->update(ql, qr, x);
        maintain();
    }
    Triple query(int ql, int qr) {
        if (qr < l || r < ql)
            return zeros;
        if (ql <= l && r <= qr)
            return s;
        push_down();
        return lc->query(ql, qr) + rc->query(ql, qr);
    }
} *segt;
SegT *build(int l, int r) {
    if (l > r)
        return NULL;
    if (l == r)
        return new SegT(l, r, NULL, NULL);
    int mid = (l + r) >> 1;
    return new SegT(l, r, build(l, mid), build(mid + 1, r));
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    static int m, l, r, x;
    static ll p, q, g;
    static char opt[5];
    static Triple res;
    scanf("%d%d", &n, &m);
    --n;
    for (l = 1; l <= n; ++l)
        ssq[l] = ssq[l - 1] + (ll)l * l;
    segt = build(1, n);
    while (m--) {
        scanf("%s%d%d", opt, &l, &r);
        if (opt[0] == 'C')
            scanf("%d", &x), segt->update(l, r - 1, x);
        else {
            res = segt->query(l, r - 1);
            p = (ll)(r - (ll)l * r) * res.x[0] + (ll)(l + r - 1) * res.x[1] - res.x[2];
            q = (ll)(r - l + 1) * (r - l) / 2;
            g = gcd(p, q);
            printf("%lld/%lld\n", p / g, q / g);
        }
    }

    return 0;
}
