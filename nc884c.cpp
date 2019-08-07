#include <akari>

IO<1000000, 1000000> io;

cint N = 3000002;

int a[N], sta[N], scnt, next[N], prev[N];
ll s[N];
struct Node {
    Node *lc, *rc;
    ll min, max;
    Node() {}
    Node(ll x) : min(x), max(x) {}
    Node(Node *l, Node *r) : lc(l), rc(r) { maintain(); }
    void maintain() {
        min = std::min(lc->min, rc->min);
        max = std::max(lc->max, rc->max);
    }
#define QUERYER(func, attr, add, zero) \
    ll func(int ql, int qr, int l, int r) { \
        if (ql <= l && r <= qr) \
            return attr; \
        int mid = (l + r) >> 1; \
        ll res = zero; \
        if (ql <= mid) \
            res = add(res, lc->func(ql, qr, l, mid)); \
        if (qr > mid) \
            res = add(res, rc->func(ql, qr, mid + 1, r)); \
        ccc(ql, qr, l, r, res); \
        return res; \
    }
    QUERYER(qmin, min, std::min, LLONG_MAX);
    QUERYER(qmax, max, std::max, LLONG_MIN);
} pool[N << 1], *curr = pool, *segt;

Node *build(int l, int r) {
    if (l == r)
        return new (curr++) Node(s[l]);
    int mid = (l + r) >> 1;
    return new (curr++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
    int n = io;
    rep (i, 1, n) {
        io >> a[i];
        while (scnt && a[sta[scnt]] >= a[i])
            --scnt;
        prev[i] = sta[scnt];
        sta[++scnt] = i;
    }
    scnt = 0; // **
    per (i, n, 1) {
        while (scnt && a[sta[scnt]] >= a[i])
            --scnt;
        next[i] = scnt ? sta[scnt] : (n + 1);
        sta[++scnt] = i;
    }
    rep (i, 1, n)
        s[i] = s[i - 1] + (int)io;
    segt = build(0, n);

    ll ans = LLONG_MIN;
    rep (i, 1, n) {
        if (a[i] > 0)
            ans = std::max(ans, a[i] * (segt->qmax(i, next[i] - 1, 0, n) - segt->qmin(prev[i], i, 0, n)));
        else if (a[i] == 0)
            ans = std::max(ans, 0ll);
        else
            ans = std::max(ans, a[i] * (segt->qmin(i, next[i] - 1, 0, n) - segt->qmax(prev[i], i, 0, n)));
    }
    io << ans daze;


    return 0;
}
