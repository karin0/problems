#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;

#ifdef AKARI
void cca() {
    std::cerr << "\033[39;0m" << std::endl;
}
template <typename T, typename... Args>
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", cca(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

const int N = 100003;
int a[N], pos[N];
int res, qr, n;
struct Node {
    int mx;
    // std::set<int> s;
    Node *lc, *rc;
    Node() {}
    Node(Node *lc, Node *rc) : lc(lc), rc(rc) {
        maintain();
    }
    Node(int x) : mx(x) {
        ccc(mx, x);
    }
        // s.clear();
        // s.insert(x);

    void maintain() {
        mx = std::max(lc->mx, rc->mx);
    }
    void qry(int qql, int qqr, int l, int r) const {
        ccc("qry", qql, qqr, l, r);
        if (qql <= l && r <= qqr)
            return qry2(l, r);
        int mid = (l + r) >> 1;
        if (qql <= mid)
            lc->qry(qql, qqr, l, mid);
        if (qqr > mid)
            rc->qry(qql, qqr, mid + 1, r);
    }
    void qry2(int l, int r) const {
        ccc("qry2", l, r);
        if (l == r) {
            if (mx > qr)
                res = std::min(res, l);
            return;
        }
        int mid = (l + r) >> 1;
        ccc(lc->mx, rc->mx, qr);
        if (lc->mx > qr)
            lc->qry2(l, mid);
        else if (rc->mx > qr)
            rc->qry2(mid + 1, r);
    }
    void del(int l, int r) {
        if (l == r)
            return (void)(mx = n + 1);
        int mid = (l + r) >> 1;
        if (qr <= mid)
            lc->del(l, mid);
        else
            rc->del(mid + 1, r);
        maintain();
    }
} pool[N << 1], *curr;
Node *build(int l, int r) {
    if (l == r) {
        ccc(l, pos[l]);
        return new (curr++) Node(pos[l]);
    }
    int mid = (l + r) >> 1;
    return new (curr++) Node(build(l, mid), build(mid + 1, r));
    // o->lc->fa = o->rc->fa = o;
    // rep (i, l, r)
    //    o->s.insert(pos[i]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int m, mx = 1;
        scanf("%d%d", &n, &m);
        rep (i, 1, n) {
            scanf("%d", &a[i]);
            mx = std::max(mx, a[i]);
            pos[a[i]] = i;
        }
        rep (i, 1, mx) if (!pos[i])
            pos[i] = n + 1;
        curr = pool;
        Node *segt = build(1, mx);
        int la = 0;
        while (m--) {
            int op, x, y;
            scanf("%d%d", &op, &x);
            if (op == 1) {
                x ^= la;
                ccc(1, x);
                if (a[x]) {
                    qr = a[x];
                    segt->del(1, mx);
                    a[x] = 0;
                }
            } else {
                scanf("%d", &y);
                x ^= la;
                y ^= la;
                ccc(2, x, y);
                if (y > mx) {
                    la = y;
                } else {
                    qr = x;
                    res = mx + 1;
                    segt->qry(y, mx, 1, mx);
                    la = res;
                }
                ccc(la);
                printf("%d\n", la);
            }
        }
    }
}