#include <cstdio>
#include <algorithm>
#include <climits>

typedef long long ll;
const int N = 1000005;
int n, a[N];
struct SegT {
    SegT *lc, *rc;
    int l, r;
    int max, tag;
    SegT(int _l, int _r, SegT *_lc, SegT *_rc) : lc(_lc), rc(_rc), l(_l), r(_r), max(a[_l]), tag(INT_MIN) {
        maintain();
    }
    void cover(int v) {
        max = v;
        tag = v;
    }
    void push_down() {
        if (tag != INT_MIN) {
            lc->cover(tag);
            rc->cover(tag);
            tag = INT_MIN;
        }
    }
    void maintain() {
        if (lc)
            max = std::max(lc->max, rc->max);
    }
    void update(int ql, int qr, int v) {
        if (ql <= l && r <= qr) {
            cover(v);
            return;
        }
        if (qr < l || r < ql)
            return;
        push_down();
        lc->update(ql, qr, v);
        rc->update(ql, qr, v);
        maintain();
    }
    int query(int ql, int qr) {
        if (ql <= l && r <= qr)
            return max;
        if (qr < l || r < ql)
            return INT_MIN;
        push_down();
        return std::max(lc->query(ql, qr), rc->query(ql, qr));
    }
} *segt;
SegT *build(int l, int r) {
    if (l == r)
        return new SegT(l, r, NULL, NULL);
    int mid = (l + r) >> 1;
    return new SegT(l, r, build(l, mid), build(mid + 1, r));
}

int main() {
    static int m, i, l, r, opt, v;
    scanf("%d%d%d%d%d%d", &n, &m, &opt, &l, &r, &v);
    a[1] = opt;
    for (i = 2; i <= n; ++i)
        a[i] = ((ll)a[i - 1] * l % v + r) % v;
    segt = build(1, n);
    while (m--) {
        scanf("%d%d%d", &opt, &l, &r);
        if (opt == 0)
            printf("%d\n", segt->query(l, r));
        else
            scanf("%d", &v), segt->update(l, r, v);
    }

    return 0;
}
