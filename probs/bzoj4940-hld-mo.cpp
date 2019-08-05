#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))

typedef long long ll;
const int N = 100055, M = 500055;
int n, a[N], bel[N];
struct Node {
    int x, dfn, dep, siz;
    Node *fa, *top, *hch;
    struct Edge *e;
} g[N], *rt, *cap;
struct Edge {
    Node *v;
    Edge *e;
} es[N * 2];
void arc(Node *u, Node *v) {
    static Edge *curr = es;
    *curr = Edge{v, u->e};
    u->e = curr;
    ++curr;
}
void dfs1(Node *u) {
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->e) if (!(v = e->v)->siz) {
        v->fa = u;
        v->dep = u->dep + 1;
        dfs1(v);
        u->siz += v->siz;
        if (!u->hch || v->siz > u->hch->siz)
            u->hch = v;
    }
}
void dfs2(Node *u, Node *t) {
    static int tim;
    a[tim] = u->x;
    u->dfn = tim++;
    // printf("dfn %ld is %d\n", u-g,u->dfn);
    u->top = t;
    if (u->hch)
        dfs2(u->hch, t);
    for (Edge *e = u->e; e; e = e->e)
        if (e->v->fa == u && e->v != u->hch)
            dfs2(e->v, e->v);
}
void hld_init() {
    rt->dep = 1;
    dfs1(rt);
    dfs2(rt, rt);
}
int s, ocnt;
struct Query {
    int l, r;
    bool add;
    ll *res;
    bool operator < (const Query &rhs) const {
        static int i, j;
        i = bel[l], j = bel[rhs.l];
        return i < j || (i == j && r < rhs.r);
    }
} qwq[M * 9];
void get_ranges(const Node *u, int &l1, int &r1, int &l2, int &r2) {
    static Node *p;
    if (cap == rt)
        l1 = u->dfn, r1 = u->dfn + u->siz - 1, l2 = 0, r2 = -1;
    else if (cap == u)
        l1 = 0, r1 = n - 1, l2 = 0, r2 = -1;
    else {
        for (p = cap; p; p = p->top->fa) {
            if (p->top->fa == u) {
                p = p->top;
                break;
            }
            if (p->top == u->top) {
                p = p->dep < u->dep ? NULL : u->hch;
                break;
            }
        }
        if (p) {
            l1 = 0, r1 = p->dfn - 1, l2 = p->dfn + p->siz, r2 = n - 1;
            if (l2 > r2)
                l2 = 0, r2 = -1;
        } else
            l1 = u->dfn, r1 = u->dfn + u->siz - 1, l2 = 0, r2 = -1;
    }
}
inline void add_query(const int l, const int r, const bool add, ll *res) {
    if (l >= 0 && r >= 0)
        qwq[ocnt++] = Query{l, r, add, res};
}
inline void make_query(const Node *u, const Node *v, ll *res) {
    static int l1, r1, l2, r2, l3, r3, l4, r4;
    get_ranges(u, l1, r1, l2, r2);
    get_ranges(v, l3, r3, l4, r4);
    --l1, --l2, --l3, --l4;
    add_query(r1, r3, true, res);
    add_query(r1, r4, true, res);
    add_query(r1, l3, false, res);
    add_query(r1, l4, false, res);
    add_query(r2, r3, true, res);
    add_query(r2, r4, true, res);
    add_query(r2, l3, false, res);
    add_query(r2, l4, false, res);
    add_query(l1, r3, false, res);
    add_query(l1, r4, false, res);
    add_query(l1, l3, true, res);
    add_query(l1, l4, true, res);
    add_query(l2, r3, false, res);
    add_query(l2, r4, false, res);
    add_query(l2, l3, true, res);
    add_query(l2, l4, true, res);
}

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return s == t ? -1 : *s++;
    }
    operator int() {
        static int x;
        static char c;
        static bool neg;
        x = 0;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if (c == '-')
            neg = true, c = gc();
        else
            neg = false;
        for (; isdigit(c); c = gc())
            x = x * 10 + c - '0';
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
    void print(T x) {
        static char c[30], *q;
        static int y;
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
    }
    inline void flush() {
        fwrite(b, 1, p - b, stdout);
    }
} io;
int main() {
    static int m, i, u, v, opt, set[N], *end, qcnt, l, r, cl[N], cr[N];
    static ll ans, res[M];
    n = io, m = io;
    rep (i, 1, n)
        g[i].x = set[i] = io;
    set[0] = set[n];
    std::sort(set, set + n);
    end = std::unique(set, set + n);
    rep (i, 1, n)
        g[i].x = std::lower_bound(set, end, g[i].x) - set;
    re (i, 1, n) {
        u = io, v = io;
        arc(&g[u], &g[v]);
        arc(&g[v], &g[u]);
    }
    rt = cap = &g[1];
    hld_init();
    re (i, 0, m) {
        opt = io, u = io;
        if (opt == 1)
            cap = &g[u];
        else
            v = io, make_query(&g[u], &g[v], &res[qcnt++]);
    }
    s = floor(4 * n / sqrt(ocnt) + 0.5);
    re (i, 0, n)
        bel[i] = i / s;
    std::sort(qwq, qwq + ocnt);
    l = r = -1, ans = 0;
    re (i, 0, ocnt) {
        const Query &q = qwq[i];
        while (l < q.l)
            ++l, ++cl[a[l]], ans += cr[a[l]];
        while (r < q.r)
            ++r, ++cr[a[r]], ans += cl[a[r]];
        while (q.l < l)
            --cl[a[l]], ans -= cr[a[l]], --l;
        while (q.r < r)
            --cr[a[r]], ans -= cl[a[r]], --r;
        q.add ? *q.res += ans : (*q.res -= ans);
    }
    re (i, 0, qcnt)
        io.print(res[i]), io.pc('\n');
    io.flush();

    return 0;
}
