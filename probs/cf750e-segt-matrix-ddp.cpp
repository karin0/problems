#include <akari>

IO<1000000, 1000000> io;

cint N = 200002, inf = 0x3f3f3f3f;

/*
    0: x
    1: 2x
    2: 20x
    3: 201x
    4: 2017
*/

struct S {
    int a[5][5];
    S operator * (const S &rhs) const {
        S ret;
        rep (i, 0, 4) {
            cint *ai = a[i];
            int *rai = ret.a[i];
            rep (j, 0, 4) {
                int &r = rai[j] = ai[0] + rhs.a[0][j];
                rep (k, 1, 4)
                    r = std::min(r, ai[k] + rhs.a[k][j]);
            }
        }
        return ret;
    }
} ts[10];

struct Node {
    Node *lc, *rc;
    S a;
    Node() {}
    Node(int x) : a(ts[x]) {}
    Node(Node *l, Node *r) : lc(l), rc(r), a(l->a * r->a) {}
    S query(int ql, int qr, int l, int r) {
        if (ql <= l && r <= qr)
            return a;
        int mid = (l + r) >> 1;
#define LQ lc->query(ql, qr, l, mid)
#define RQ rc->query(ql, qr, mid + 1, r)
        if (ql <= mid) {
            if (qr > mid)
                return LQ * RQ;
            else
                return LQ;
        } else
            return RQ;
    }
} pool[N << 1], *curr = pool;

char a[N];
Node *build(int l, int r) {
    if (l == r)
        return new (curr++) Node(a[l] - '0');
    int mid = (l + r) >> 1;
    return new (curr++) Node(build(l, mid), build(mid + 1, r));
}

int main() {
    memset(ts, 0x3f, sizeof(ts));
    rep (i, 0, 9)
        rep (j, 0, 4)
            ts[i].a[j][j] = 0;
#define F(i, p)                \
        ts[i].a[p][p] = 1;     \
        ts[i].a[p][p + 1] = 0;
    F(2, 0);
    F(0, 1);
    F(1, 2);
    F(7, 3);
    ts[6].a[3][3] = ts[6].a[4][4] = 1;

    int n, q;
    io >> n >> q;
    io.gs(a + 1);
    Node *segt = build(1, n);
    while (q--) {
        int l, r;
        io >> l >> r;
        int t = segt->query(l, r, 1, n).a[0][4];
        if (t >= 0x3f3f3f3f)
            io.pc('-'), io.pc('1');
        else
            io << t;
        io.pc('\n');
    }
}
