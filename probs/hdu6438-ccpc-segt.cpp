#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

int a[N], b[N];
bool cmp(cint i, cint j) {
    return a[i] > a[j] || (a[i] == a[j] && i > j); 
}

struct Node {
    Node *lc, *rc;
    int x;
    Node() {}
    Node(int x) : x(x) {}
    Node(Node *l, Node *r) : lc(l), rc(r) {
        maintain();
    }
    static int min(int i, int j) {
        return a[i] < a[j] ? i : j;
    }
    void maintain() {
        x = min(lc->x, rc->x);
    }
    int query(int ql, int qr, int l, int r) {
        if (ql <= l && r <= qr)
            return x;
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res = lc->query(ql, qr, l, mid);
        if (qr > mid)
            res = res ? min(res, rc->query(ql, qr, mid + 1, r)) : rc->query(ql, qr, mid + 1, r);
        return res;
    }
    void update(int i, int l, int r) {
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        if (i <= mid)
            lc->update(i, l, mid);
        else
            rc->update(i, mid + 1, r);
        maintain();
    }
} pool[N << 1], *curr;
Node *build(int l, int r) {
    if (l == r)
        return new (curr++) Node(l);
    int mid = (l + r) >> 1;
    return new (curr++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
    int T;
    io > T;
    while (T--) {
        int n;
        io > n;
        rep (i, 1, n) {
            io > a[i];
            b[i] = i;
        }
        std::sort(b + 1, b + n + 1, cmp);
        curr = pool;
        Node *segt = build(1, n);
        ll ans = 0;
        int ans2 = 0;
        rep (i, 1, n) {
            int j = b[i];
            if (j == 1 || a[j] == INT_MAX)
                continue;
            int p = segt->query(1, j - 1, 1, n);
            if (a[p] == INT_MAX)
                continue;
            int t = a[j] - a[p];
            if (t > 0) {
                ans += t;
                ans2 += 2;
                a[p] = INT_MAX;
                segt->update(p, 1, n);
                a[j] = INT_MAX;
                segt->update(j, 1, n);
            }
        }
        (((io < ans) << ' ') < ans2) << '\n';
    }
}
