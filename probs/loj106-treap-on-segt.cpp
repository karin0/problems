#pragma GCC optimize ("O3")
#include <cstdio>
#include <cctype>
#include <algorithm>
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
        return *s++; // return s == t ? -1 : *s++;
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
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 50007, inf = 0x7fffffff;
int n, a[N], amax = -inf, amin = inf;
namespace ds {
    struct Treap {
        Treap *lc, *rc;
        int v, pri, siz;
        Treap() {}
        Treap(const int _x) : v(_x), pri(rand()), siz(1) {}
        void *operator new (size_t) {
            static Treap pool[N * 2 * 17], *curr = pool;
            return ++curr;
        }
        inline void maintain() {
            siz = 1;
            if (lc)
                siz += lc->siz;
            if (rc)
                siz += rc->siz;
        }
    };
    void split(Treap *o, const int x, Treap *&p, Treap *&q) { // p <- <= x
        if (!o) {
            p = q = NULL;
            return;
        }
        if (x < o->v) {
            q = o;
            split(o->lc, x, p, o->lc);
        } else {
            p = o;
            split(o->rc, x, o->rc, q);
        }
        o->maintain();
    }
    Treap *merge(Treap *p, Treap *q) {
        if (!p)
            return q;
        if (!q)
            return p;
        if (p->pri < q->pri) {
            p->rc = merge(p->rc, q);
            p->maintain();
            return p;
        } else {
            q->lc = merge(p, q->lc);
            q->maintain();
            return q;
        }
    }
    namespace hd {
        Treap *p, *q, *r;
        int res;
        inline void insert(Treap *&o, const int x) {
            split(o, x, p, q);
            o = merge(merge(p, new Treap(x)), q);
        }
        inline void erase(Treap *&o, const int x) {
            split(o, x, p, r);
            split(p, x - 1, p, q);
			o = merge(merge(p, merge(q->lc, q->rc)), r);
        }
        inline int rank(Treap *&o, const int x) {
			// if (o->siz == 1)
			//	return o->v < x;
            split(o, x - 1, p, q);
            res = p ? p->siz : 0;
            o = merge(p, q);
            return res;
        }
        int pred(Treap *&o, const int x) {
            split(o, x - 1, p, q);
            if (!p)
                return -inf;
            for (r = p; r->rc; r = r->rc);
            o = merge(p, q);
            return r->v;
        }
        int succ(Treap *&o, const int x) {
            split(o, x, p, q);
            if (!q)
                return inf;
            for (r = q; r->lc; r = r->lc);
            o = merge(p, q);
            return r->v;
        }
    }
    struct SegT {
        Treap *bst;
        SegT *lc, *rc;
        SegT() {}
        SegT(SegT *const _lc, SegT *const _rc) : lc(_lc), rc(_rc) {}
        void *operator new (const size_t) {
            static SegT pool[N * 4], *curr = pool;
            return ++curr;
        }
        void update(const int i, const int old, const int x, const int l = 1, const int r = n) {
            // printf("In %d, %d, replace %d to %d at %d\n",l,r,old,x,i);
            hd::erase(bst, old);
            hd::insert(bst, x);
            if (l != r) {
                int mid = (l + r) >> 1;
                if (i <= mid)
                    lc->update(i, old, x, l, mid);
                else
                    rc->update(i, old, x, mid + 1, r);
            }
        }
        int rank(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
            if (ql <= l && r <= qr)
				return hd::rank(bst, x);
            int mid = (l + r) >> 1, res = 0;
            if (ql <= mid)
                res += lc->rank(ql, qr, x, l, mid);
            if (qr > mid)
                res += rc->rank(ql, qr, x, mid + 1, r);
            // printf("In %d, %d, %d is rk %d for %d, %d\n",l,r,x,res,ql,qr);
            return res;
        }
        int pred(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
            if (ql <= l && r <= qr)
                return hd::pred(bst, x);
            int mid = (l + r) >> 1, res = -inf;
            if (ql <= mid)
                res = std::max(res, lc->pred(ql, qr, x, l, mid));
            if (qr > mid)
                res = std::max(res, rc->pred(ql, qr, x, mid + 1, r));
            return res;
        }
        int succ(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
            if (ql <= l && r <= qr)
                return hd::succ(bst, x);
            int mid = (l + r) >> 1, res = inf;
            if (ql <= mid)
                res = std::min(res, lc->succ(ql, qr, x, l, mid));
            if (qr > mid)
                res = std::min(res, rc->succ(ql, qr, x, mid + 1, r));
            return res;
        }
    } *segt;
    SegT *build(const int l, const int r) {
        static int i;
        if (l == r) {
            SegT *o = new SegT;
            o->bst = new Treap(a[r]);
            return o;
        }
        int mid = (l + r) >> 1;
        SegT *o = new SegT(build(l, mid), build(mid + 1, r));
        o->bst = new Treap(a[r]);
        re (i, l, r)
            hd::insert(o->bst, a[i]);
        return o;
    }
    int kth(const int l, const int r, const int k) {
        static int lb, rb, x;
        lb = amin, rb = amax + 1;
        while (rb - lb > 1) {
            x = (lb + rb) >> 1;
            (segt->rank(l, r, x) <= k ? lb : rb) = x;
        }
        return lb;
        // return hd::rank(segt->bst, lb) == k ? lb : rb;
    }
}
int main() {
    static int m, op, l, r, i, x;
    srand(19260818);
    n = io;
    m = io;
    rep (i, 1, n) {
        x = io;
        amax = std::max(amax, x);
        amin = std::min(amin, x);
        a[i] = x;
    }
    ds::segt = ds::build(1, n);
    while (m--) {
        op = io;
        l = io;
        r = io;
        if (op == 3)
            ds::segt->update(l, a[l], r), a[l] = r;
        else {
            x = io;
            switch (op) {
                case 1: io.print(ds::segt->rank(l, r, x) + 1); break;
                case 2: io.print(ds::kth(l, r, x - 1)); break;
                case 4: io.print(ds::segt->pred(l, r, x)); break;
                default: io.print(ds::segt->succ(l, r, x));
            }
        }
    }
    io.flush();

    return 0;
}
