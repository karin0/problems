#include <cstdio>
#include <cctype>
#include <cmath>
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

const int N = 200007, inf = 0x7f7f7f7f;
int n, m, a[N];
double ori[N];
std::pair<double, int> hash[N];
struct SegT {
    SegT *lc, *rc;
    int smin, smax, tags;
    bool tagc;
    double sum;
    SegT() {}
    SegT(const int i) : smin(i), smax(i), tags(inf), sum(ori[i]) {}
    SegT(SegT *const _lc, SegT *const _rc) : lc(_lc), rc(_rc), tags(inf) {
        maintain();
    }
    void *operator new (size_t) {
        static SegT pool[N * 4], *curr = pool;
        return curr++;
    }
    inline void maintain() {
        smin = std::min(lc->smin, rc->smin);
        smax = std::max(lc->smax, rc->smax);
        sum = lc->sum + rc->sum;
    }
    inline void cover_clear() {
        sum = 0;
        tagc = true;
    }
    inline void cover_split(const int x) {
        smin = smax = tags = x;
    }
    inline void push_down() {
        if (tagc) {
            lc->cover_clear();
            rc->cover_clear();
            tagc = false;
        }
        if (tags != inf) {
            lc->cover_split(tags);
            rc->cover_split(tags);
            tags = inf;
        }
    }
    void update_split(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
            cover_split(x);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->update_split(ql, qr, x, l, mid);
        if (qr > mid)
            rc->update_split(ql, qr, x, mid + 1, r);
        maintain();
    }
    void update_clear(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
            cover_clear();
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->update_clear(ql, qr, l, mid);
        if (qr > mid)
            rc->update_clear(ql, qr, mid + 1, r);
        maintain();
    }
    void update_sum(const int i, const double x, const int l = 1, const int r = n) {
        if (l == r) {
            // printf("!!!!Update %d to %f\n",i,x);
            sum = x;
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (i <= mid)
            lc->update_sum(i, x, l, mid);
        else
            rc->update_sum(i, x, mid + 1, r);
        maintain();
    }
    void query_split(const int ql, const int qr, int &rmn, int &rmx, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
        // printf("On %d, %d for %d, %d adds %f\n",l,r,ql,qr,sum);
            rmn = std::min(rmn, smin);
            rmx = std::max(rmx, smax);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->query_split(ql, qr, rmn, rmx, l, mid);
        if (qr > mid)
            rc->query_split(ql, qr, rmn, rmx, mid + 1, r);
    }
    void query(const int ql, const int qr, double &rs, int &rmn, int &rmx, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
        // printf("On %d, %d for %d, %d adds %f\n",l,r,ql,qr,sum);
            rs += sum;
            rmn = std::min(rmn, smin);
            rmx = std::max(rmx, smax);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->query(ql, qr, rs, rmn, rmx, l, mid);
        if (qr > mid)
            rc->query(ql, qr, rs, rmn, rmx, mid + 1, r);
    }
} *segt;
SegT *build(const int l, const int r) {
    if (l == r)
        return new SegT(l);
    int mid = (l + r) >> 1;
    return new SegT(build(l, mid), build(mid + 1, r));
}
struct ValueSegT {
    ValueSegT *lc, *rc;
    int cnt;
    double sum;
    void *operator new (size_t) {
        static ValueSegT pool[N * 18 * 2], *curr = pool;
        return curr++;
    }
    inline void maintain() { 
        cnt = (lc ? lc->cnt : 0) + (rc ? rc->cnt : 0);
        sum = (lc ? lc->sum : 0) + (rc ? rc->sum : 0);
    }
    inline int rank() const {
        return lc ? lc->cnt : 0;
    }
} *set[N];
void insert(ValueSegT *& o, const int i, const int l = 1, const int r = n) {
    if (!o)
        o = new ValueSegT;
    if (l == r) {
        ++o->cnt;
        o->sum += hash[l].first;
        return;
    }
    int mid = (l + r) >> 1;
    if (i <= mid)
        insert(o->lc, i, l, mid);
    else
        insert(o->rc, i, mid + 1, r);
    o->maintain();
}
void split(ValueSegT *o, ValueSegT *&p, const int k) { // keeps only the least k values
    /*if (!o) {
        p = NULL;
        return;
    }*/
    if (!p)
        p = new ValueSegT;
    p->lc = p->rc = NULL; // ************************************************************************
    int rk = o->rank();
    if (k <= rk) {
        p->rc = o->rc;
        o->rc = NULL;
        if (k < rk)
            split(o->lc, p->lc, k);
    } else
        split(o->rc, p->rc, k - rk);
    o->maintain();
    p->maintain();
}
// int mcnt, ccnt;
void merge(ValueSegT *&o, ValueSegT *p) {
    if (!p)
        // o = NULL; // ***************************
        return;
    if (!o) {
        o = p;
        return;
    }
    merge(o->lc, p->lc);
    merge(o->rc, p->rc);
    // ++mcnt;
    // p = NULL;
    o->maintain();
}
/*ValueSegT *merge(ValueSegT *o, ValueSegT *p) {
    if (!p)
        return o;
    if (!o)
        return p;
    if (o->cnt < p->cnt)
        std::swap(o, p);
    o->lc = merge(o->lc, p->lc);
    o->rc = merge(o->rc, p->rc);
    // p = NULL;
    ++mcnt;
    o->maintain();
    return o;
}*/
inline double query_sum(const ValueSegT *const o, const int k) { // query the sum of the least k values
    if (!o || k <= 0) // ****************
        return 0.0;
    if (o->cnt <= k)
        return o->sum;
    return query_sum(o->lc, k) + query_sum(o->rc, k - o->rank());
}
int lr[N], rr[N];
bool down[N];
void sort(const int l, const int r, const bool d) {
    static int ls, rs, s, t;
    segt->query_split(l, r, ls = inf, rs = -inf);
    if ((s = lr[ls]) < l) {
        if (down[s]) {
            split(set[s], set[l], ls - l + 1);
            std::swap(set[s], set[l]);
        } else
            split(set[s], set[l], l - s);
        lr[ls] = l;
        lr[l - 1] = s;
        rr[s] = l - 1;
        down[l] = down[s];
        segt->update_split(s, l - 1, l - 1);
        segt->update_clear(s, l - 1);
        // printf("Because of %d\n", s);
        segt->update_sum(s, set[s]->sum);
    }
    if (rs > r) {
        t = lr[rs];
        if (down[t]) { // *********
            split(set[t], set[r + 1], rs - r);
            std::swap(set[t], set[r + 1]);
        } else
            split(set[t], set[r + 1], r - t + 1);
        lr[rs] = r + 1;
        rr[r + 1] = rs;
        down[r + 1] = down[t];
        segt->update_split(r + 1, rs, rs);
        segt->update_clear(r + 1, rs);
        // printf("Because of %d\n", r + 1);
        segt->update_sum(r + 1, set[r + 1]->sum);
    }
    for (t = ls + 1; t <= r; t = rr[t] + 1)
        merge(set[l], set[t]);
    /*if (m % 500 == 0)
        printf("m = %d, %d mergings takes %d time\n",m,ccnt,mcnt);*/
    lr[r] = l;
    rr[l] = r;
    down[l] = d; // *********** 
    segt->update_split(l, r, r);
    segt->update_clear(l, r);
    // printf("Because of %d\n", r + 1);
    segt->update_sum(l, set[l]->sum);
}
double query(const int l, const int r) {
    static int ls, rs, s, t;
    static double res;
	// printf("Ready\n");
    segt->query(l, r, res = 0, ls = inf, rs = -inf);
    // printf("ls = %d, rs = %d, Origin res for %d, %d is %f\n",ls,rs,l,r,res);
    if ((s = lr[ls]) < l)
        res += down[s] ? query_sum(set[s], ls - l + 1)
                       : (set[s]->sum - query_sum(set[s], l - s));
    if (rs > r) {
        t = lr[rs];
        res -= down[t] ? query_sum(set[t], rs - r)
                       : (set[t]->sum - query_sum(set[t], r - t + 1));
    }
    return res;
}
int main() {
    static int op, l, r, i;
    static double lg[20]; // rrr;// *end;
    n = io;
    m = io;
    rep (i, 1, n)
        hash[i] = std::make_pair(ori[i] = log10((int)io), i);
    std::sort(hash + 1, hash + n + 1);
    rep (i, 1, n)
        a[hash[i].second] = i;    
    rep (i, 1, n)
        insert(set[lr[i] = rr[i] = i] = new ValueSegT, a[i]);
    segt = build(1, n);
	/* rep (i, 1, n) {
	    double rrr = 0;
		int ppp = inf, qqq = -inf;
		segt->query(i, i, rrr, ppp, qqq);
		printf("%d got %f\n",i,rrr);
		while (rrr != ori[i] || ppp != i || qqq != i)
			puts("dm");
	} */
    re (i, 1, 10)
        lg[i] = log10(i);

    while (m--) {
        //if (m % 1000 == 0)
        //    fprintf(stderr, "%d left\n", m);
        op = io;
        l = io;
        r = io;
        if (op == 1)
            sort(l, r, !(int)io);
        else {
            static double res;
            res = query(l, r);
            // printf("Final ans for %d, %d is %f\n",l,r,res);
            io.print((int)(std::upper_bound(lg + 1, lg + 10, res - floor(res)) - lg) - 1);
            // io.print((int)floor(pow(10, res - floor(res))));
        }
    }

    io.flush(); // ***
    return 0;
}
