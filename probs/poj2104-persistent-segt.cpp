#include <cstdio>
#include <algorithm>
#include <new>

const int N = 100005, B = 280 * N;

size_t nsiz;
void *alloc() {
    static char buf[B], *cur = buf;
    if (cur == buf + B)
        return malloc(nsiz);
    char *p = cur;
    cur += nsiz;
    return p;
}
struct Node {
    int l, r;
    Node *lc, *rc;
    int cnt;
    Node (const int _l, const int _r, Node *_lc = NULL, Node *_rc = NULL) : l(_l), r(_r), lc(_lc), rc(_rc), cnt((_lc ? _lc->cnt : 0) + (_rc ? _rc->cnt : 0)) {}
    Node (const int _l, const int _r, const int _c) : l(_l), r(_r), cnt(_c) {}
    
    void push_down() {
        if (lc && rc)
            return;
        int mid = (l + r) >> 1;
        if (!lc)
            lc = new (alloc()) Node(l, mid);
        if (!rc)
            rc = new (alloc()) Node(mid + 1, r);
    }
    Node *insert(const int x) {
        if (x < l || x > r)
            return this;
        if (x == l && x == r)
            return new (alloc()) Node(l, r, cnt + 1);
        int mid = (l + r) >> 1;
        push_down();
        if (x <= mid)
            return new (alloc()) Node(l, r, lc->insert(x), rc);
        else
            return new (alloc()) Node(l, r, lc, rc->insert(x));
    }
    int rank() const {
        return lc ? lc->cnt : 0;
    }
} *root[N];
int n, mx;
void build(const int a[]) {
    static int i;
    root[0] = new (alloc()) Node(1, mx);
    for (i = 1; i <= n; ++i)
        root[i] = root[i - 1]->insert(a[i]);
}
int query(const int l, const int r, int k) {
    static Node *lt, *rt;
    static int lb, rb, t, mid;
    lt = root[l - 1], rt = root[r];
    lb = 1, rb = mx;
    while (lb < rb) {
        lt->push_down(), rt->push_down();
        t = rt->rank() - lt->rank();
        mid = (lb + rb) >> 1;
        if (k <= t)
            lt = lt->lc, rt = rt->lc, rb = mid;
        else
            lt = lt->rc, rt = rt->rc, lb = mid + 1, k -= t;
    }
    return lb;
}
int main() {
    nsiz = sizeof(Node);
    static int m, a[N], set[N], i, *end, l, r, k;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", &a[i]), set[i] = a[i];
    std::sort(set + 1, set + n + 1);
    end = std::unique(set + 1, set + n + 1);
    mx = end - set - 1;
    for (i = 1; i <= n; ++i)
        a[i] = std::lower_bound(set + 1, end, a[i]) - set;
    build(a);
    while (m--) {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", set[query(l, r, k)]);
    }
    

    return 0;
}
