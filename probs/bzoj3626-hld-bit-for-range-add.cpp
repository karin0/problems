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
const int N = 50003, mo = 201314;
inline void madd(int &x, const int v) {
    x += v;
    if (x >= mo)
        x -= mo;
    else if (x < 0)
        x += mo;
}
inline int mmod(const ll v) {
    return v < 0 ? (v % mo + mo) % mo : v % mo;
}
int n;
struct Node {
    int dep, dfn, siz;
    Node *hch, *fa, *top;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
    void *operator new (size_t) {
        static Edge pool[N * 2], *curr = pool;
        return curr++;
    }
};
void dfs1(Node *const u) {
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->e) {
        v = e->v;
        v->dep = u->dep + 1;
        v->fa = u;
        dfs1(v);
        u->siz += v->siz;
        if (!u->hch || v->siz > u->hch->siz)
            u->hch = v;
    }
}
void dfs2(Node *const u, Node *const t) {
    static int tim;
    u->dfn = ++tim;
    u->top = t;
    // printf("%d th is %ld, its top is %ld\n", tim, u-g, t-g);
    if (u->hch)
        dfs2(u->hch, t);
    for (Edge *e = u->e; e; e = e->e)
        if (e->v != u->hch)
            dfs2(e->v, e->v);
}
namespace ds {
    struct BIT {
        int c[N];
        inline static int lowbit(const int i) {
            return i & -i;
        }
        void add(int i, const int v) {
            for (; i <= n; i += lowbit(i))
                madd(c[i], v);
        }
        int query(int i) const {
            static int res;
            for (res = 0; i > 0; i -= lowbit(i))
                madd(res, c[i]);
            return res;
        }
    } bit1, bit2;
    inline void add(const int l, int r, const int v = 1) {
        ++r;
        bit1.add(l, v);
        bit1.add(r, -v);
        bit2.add(l, v * l % mo);
        bit2.add(r, -v * r);
    }
    inline int query_suf(const int i) {
        return mmod((ll)bit1.query(i) * (i + 1) - bit2.query(i));
    }
    inline int query(const int l, const int r) {
        static int res;
        res = query_suf(r) - query_suf(l - 1);
        if (res < 0)
            res += mo;
        return res;
    }
}
inline void init() {
    g[1].dep = 1;
    dfs1(&g[1]);
    dfs2(&g[1], &g[1]);
}
void update(const Node *u) {
    while (u) {
        ds::add(u->top->dfn, u->dfn);
        u = u->top->fa;
    }
}
int query(const Node *u) {
    static int res;
    res = 0;
    while (u) {
        madd(res, ds::query(u->top->dfn, u->dfn));
        u = u->top->fa;
    }
    return res;
}
struct Query {
    int r, u, *ans;
    bool add;
    inline bool operator < (const Query &rhs) const {
        return r < rhs.r;
    }
} qwq[N << 1];
int main() {
    static int m, p, i, u, l, r, ans[N], curr;
    n = io;
    m = io;
    rep (i, 2, n)
        new Edge(&g[(int)io + 1], &g[i]);
    init();
    re (i, 0, m) {
        l = (int)io;
        r = (int)io + 1;
        u = (int)io + 1;
        qwq[p++] = (Query){r, u, &ans[i], true};
        qwq[p++] = (Query){l, u, &ans[i], false};
    }
    std::sort(qwq, qwq + p);
    re (i, 0, p) {
        const Query &q = qwq[i];
        while (curr < q.r)
            update(&g[++curr]);
        madd(*q.ans, q.add ? query(&g[q.u]) : -query(&g[q.u]));
    }
    re (i, 0, m)
        io.print(ans[i]);

    io.flush();
    return 0;
}
