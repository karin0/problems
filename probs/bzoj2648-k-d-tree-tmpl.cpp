#include <cstdio>
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
        return s == t ? -1 : *s++;
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
    inline void flush() {
        fwrite(b, 1, p - b, stdout);
    }
} io;
const int N = 500003;
struct Point {
    int x, y;
} a[N];
int dis(const Point &p, const Point &q) {
    return std::abs(p.x - q.x) + std::abs(p.y - q.y);
}
int ret;
struct Node {
    Node *ch[2];
    Point p, r1, r2;
    Node () {}
    Node(Point _p, Node *lc = NULL, Node *rc = NULL) : p(_p), r1(_p), r2(_p) {
        ch[0] = lc, ch[1] = rc;
        maintain();
    }
    void maintain() {
        static Node *o;
        if (ch[0]) {
            o = ch[0];
            r1.x = std::min(r1.x, o->r1.x);
            r1.y = std::min(r1.y, o->r1.y);
            r2.x = std::max(r2.x, o->r2.x);
            r2.y = std::max(r2.y, o->r2.y);
        }
        if (ch[1]) {
            o = ch[1];
            r1.x = std::min(r1.x, o->r1.x);
            r1.y = std::min(r1.y, o->r1.y);
            r2.x = std::max(r2.x, o->r2.x);
            r2.y = std::max(r2.y, o->r2.y);
        }
    }
    int dis_to_bound(const Point &c) const {
        static int res, d;
        res = 0;
        if ((d = r1.x - c.x) > 0)
            res += d;
        else if ((d = c.x - r2.x) > 0)
            res += d;
        if ((d = r1.y - c.y) > 0)
            res += d;
        else if ((d = c.y - r2.y) > 0)
            res += d;
        return res;
    }
    void query(const Point &c) {
        ret = std::min(ret, dis(p, c));
        if (!(ch[0] || ch[1]))
            return;
        if (ch[0] && ch[1]) {
            int d[] = {ch[0]->dis_to_bound(c), ch[1]->dis_to_bound(c)};
            int r = d[1] < d[0];
            ch[r]->query(c);
            if (d[r ^ 1] < ret)
                ch[r ^ 1]->query(c);
        } else
            ch[!ch[0]]->query(c);
    }
} _pool[N << 1], *_curr = _pool, *root;
bool cmp0(const Point &p, const Point &q) {
    return p.x < q.x || (p.x == q.x && p.y < q.y);
}
bool cmp1(const Point &p, const Point &q) {
    return p.y < q.y || (p.y == q.y && p.x < q.x);
}
Node *build(int l, int r, int d = 0) {
    if (l > r)
        return NULL;
    if (l == r)
        return new (_curr++) Node(a[l]);
    int mid = (l + r) >> 1;
    std::nth_element(a + l, a + mid, a + r + 1, d ? cmp1 : cmp0);
    return new (_curr++) Node(a[mid], build(l, mid - 1, d ^ 1), build(mid + 1, r, d ^ 1));
}
void insert(const Point &p) {
    Node **o = &root, *u;
    int d = 0;
    while (u = *o) {
        u->r1.x = std::min(p.x, u->r1.x);
        u->r1.y = std::min(p.y, u->r1.y);
        u->r2.x = std::max(p.x, u->r2.x);
        u->r2.y = std::max(p.y, u->r2.y);
        o = &u->ch[(d ? cmp1 : cmp0)(p, u->p)];
        d ^= 1;
    }
    *o = new (_curr++) Node(p);
}
int query(const Point &p) {
    ret = INT_MAX;
    root->query(p);
    return ret;
}

int main() {
    static int n, m, i;
    static Point p;
    static char op[3];
    n = io;
    m = io;
    re (i, 0, n)
        a[i].x = io, a[i].y = io;
    root = build(0, n - 1);
    while (m--) {
        io.gs(op);
        p.x = io, p.y = io;
        if (op[0] == '1')
            insert(p);
        else
            io.print(query(p));
    }

    io.flush(); // ***
    return 0;
}
