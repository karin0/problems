#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; // return s == t ? EOF : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
        *st++ = 0;
    }
    template <class T>
    operator T() {
        static T x;
        static char c;
        static bool neg;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if (c == '-')
            neg = true, c = gc();
        else
            neg = false;
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return neg ? -x : x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(b, 1, L, stdout), p = b;
        *p++ = c;
    }
    template<class T>
    void print(T x, const bool nl = true) {
        static char c[30], *q;
        static T y;
        if (x == 0)
            pc('0');
        else {
            if (x < 0)
                pc('-'), x = -x;
            for (q = c; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != c)
                pc(*--q);
        }
        if (nl)
            pc('\n');
    }
    void ps(const char *st, const bool nl = true) {
        while (*st)
            pc(*st++);
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

typedef long long ll;
const int N = 200003;
struct Vec {
    int x, y;
    Vec() {}
    Vec(const int _x, const int _y) : x(_x), y(_y) {}
    Vec(const Vec &_a, const Vec &_b) : x(_b.x - _a.x), y(_b.y - _a.y) {}
    bool operator < (const Vec &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};
inline ll dot(const Vec &a, const Vec &b) {
    return (ll)a.x * b.x + (ll)a.y * b.y;
}
inline ll cross(const Vec &a, const Vec &b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
}
int pcnt, qcnt;
struct SegT {
    SegT *lc, *rc;
    std::vector<const Vec *> conv;
    int cur;
    SegT() {}
    SegT(SegT *const _lc, SegT *const _rc) : lc(_lc), rc(_rc) {}
    void *operator new (size_t) {
        static SegT pool[N * 4], *curr = pool;
        return curr++;
    }
    void insert(const int ql, const int qr, Vec &x, const int l = 1, const int r = qcnt) {
        if (ql <= l && r <= qr) {
            insert(x);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->insert(ql, qr, x, l, mid);
        if (qr > mid)
            rc->insert(ql, qr, x, mid + 1, r);
    }
    void insert(const Vec &x) {
        while (conv.size() > 1 && cross(Vec(*conv[(int)conv.size() - 2], *conv.back()), Vec(*conv[(int)conv.size() - 2], x)) >= 0)
            conv.pop_back();
        conv.push_back(&x);
    }
    ll query(const Vec &x) {
        static ll nv, cv;
        if (conv.empty())
            return 0;
        cv = dot(*conv[cur], x);
        while (cur + 1 < (int)conv.size() && (nv = dot(*conv[cur + 1], x)) >= cv) {
            ++cur;
            cv = nv;
        }
        return cv;
    }
    ll query(const int i, const Vec &x, const int l = 1, const int r = qcnt) {
        ll res = query(x);
        if (l == r)
            return res;
        int mid = (l + r) >> 1;
        return std::max(res, i <= mid ? lc->query(i, x, l, mid) : rc->query(i, x, mid + 1, r));
    }
} *segt;
SegT *build(const int l, const int r) {
    if (l == r)
        return new SegT;
    int mid = (l + r) >> 1;
    return new SegT(build(l, mid), build(mid + 1, r));
}
struct Record {
    Vec vec;
    int l, r;
    bool operator < (const Record &rhs) const {
        return vec < rhs.vec;
    }
} vecs[N];
struct Query {
    Vec vec;
    int t;
    ll *ans;
    double slope;
    bool operator < (const Query &rhs) const {
        return slope > rhs.slope;
    }
} qwq[N];
int main() {
    static int m, op, x, y, i;
    static ll ans[N]; // ********
    m = io;
    rep (i, 1, m) {
        op = io;
        if (op == 1) {
            x = io;
            y = io;
            vecs[++pcnt] = (Record){Vec(x, y), qcnt + 1, -1};
        } else if (op == 2) {
            vecs[(int)io].r = qcnt;
        } else {
            x = io;
            y = io;
            ++qcnt;
            qwq[qcnt] = (Query){Vec(x, y), qcnt, &ans[qcnt], (double)y / x};
        }
    }
    std::sort(qwq + 1, qwq + qcnt + 1);
    std::sort(vecs + 1, vecs + pcnt + 1); // **************
    segt = build(1, qcnt);
    rep (i, 1, pcnt) {
        Record &q = vecs[i];
        if (q.r == -1)
            q.r = qcnt;
        if (q.l <= q.r)
            segt->insert(q.l, q.r, q.vec);
    }
    rep (i, 1, qcnt)
        *qwq[i].ans = segt->query(qwq[i].t, qwq[i].vec);
    rep (i, 1, qcnt)
        io.print(ans[i]);

    io.flush();
    return 0;
}
