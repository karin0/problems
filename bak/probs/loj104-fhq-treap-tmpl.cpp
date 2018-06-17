#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <climits>
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
        return *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
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
        if (neg)
            x = -x;
        return x;
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
        fwrite(b, 1, p - b, stdout);
    }
} io;

const int N = 100008;
struct Node {
    Node *ch[2];
    int v, pri, siz;

    Node() {}
    Node(const int _v) : v(_v), pri(rand()), siz(1) {}
    inline void maintain() {
        siz = 1 + (ch[0] ? ch[0]->siz : 0) + (ch[1] ? ch[1]->siz : 0);
    }
    inline int rank() const {
        return ch[0] ? ch[0]->siz : 0;
    }
} pool[N], *curr = pool;
Node *merge(Node *const p, Node *const q) { // max key in p <= min key in q
    if (!p)
        return q;
    if (!q)
        return p;
    if (p->pri < q->pri) {
        p->ch[1] = merge(p->ch[1], q);
        p->maintain();
        return p;
    } else {
        q->ch[0] = merge(p, q->ch[0]);
        q->maintain();
        return q;
    }
}
void split(Node *const o, const int x, Node *&p, Node *&q) {
    if (!o) {
        p = q = NULL;
        return;
    }
    if (x < o->v) { // ***
        split(o->ch[0], x, p, o->ch[0]);
        q = o;
    } else {
        split(o->ch[1], x, o->ch[1], q);
        p = o;
    }
    o->maintain();
}

struct Treap {
    Node *root, *p, *q, *r, *o;
    inline void insert(const int x) {
        split(root, x, p, q);
        root = merge(merge(p, new (curr++) Node(x)), q);
    }
    inline void erase(const int x) {
        split(root, x, p, r);
        split(p, x - 1, p, q);
        root = merge(merge(p, merge(q->ch[0], q->ch[1])), r);
    
    inline int pred(const int x) {
        split(root, x - 1, p, q);
        for (o = p; o->ch[1]; o = o->ch[1]);
        root = merge(p, q);
        return o->v;
    }
    inline int succ(const int x) {
        split(root, x, p, q);
        for (o = q; o->ch[0]; o = o->ch[0]);
        root = merge(p, q);
        return o->v;
    }
    inline int rank(const int x) {
        static int ret;
        split(root, x - 1, p, q);
        ret = p ? p->siz : 0;
        root = merge(p, q);
        return ret;
    }
    inline int kth(int k) {
        static int rk;
        for (p = root; ; ) {
            rk = p->rank();
            if (k < rk)
                p = p->ch[0];
            else if (k > rk)
                p = p->ch[1], k -= rk + 1;
            else
                return p->v;
        }
    }
} ds;

int main() {
    static int m, opt, x;
    srand(time(NULL)); // bzoj denies this
    m = io;
    while (m--) {
        opt = io, x = io;
        if (opt == 1)
            ds.insert(x);
        else if (opt == 2)
            ds.erase(x);
        else if (opt == 3)
            io.print(ds.rank(x) + 1);
        else if (opt == 4)
            io.print(ds.kth(x - 1));
        else if (opt == 5)
            io.print(ds.pred(x));
        else
            io.print(ds.succ(x));
    }

    io.flush(); // ***
    return 0;
}
