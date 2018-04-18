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
const int N = 100003;
int n, etlen, st[19][N * 2], lg[N * 2];
struct Node {
    int etn, siz, ms, sw, sw0, dep;
    ll sc, sc0;
    Node *vfa;
    bool done;
    struct Edge *e;
    struct VEdge *ve;
} g[N], *vrt;
struct Edge {
    Node *v;
    Edge *e;
    int w;
    Edge() {}
    Edge(Node *const _u, Node *const _v, const int _w) : v(_v), e(_u->e), w(_w) {
        _u->e = this;
    }
    void *operator new (size_t) {
        static Edge pool[N << 1], *curr = pool;
        return curr++;
    }
};
struct VEdge {
    Node *v, *p;
    VEdge *e;
    VEdge() {}
    VEdge(Node *const _u, Node *const _v, Node *const _p) : v(_v), e(_u->ve), p(_p) {
        _u->ve = this;
    }
    void *operator new (size_t) {
        static VEdge pool[N << 1], *curr = pool;
        return curr++;
    }
};
void dfs0(Node *const u) {
    st[0][u->etn = ++etlen] = u->dep;
    for (Edge *e = u->e; e; e = e->e) if (!e->v->etn) {
        e->v->dep = u->dep + e->w;
        dfs0(e->v);
        st[0][++etlen] = u->dep;
    }
}
Node *tr[N];
int cnt;
void dfs1(Node *const u, Node *const f) {
   // printf("Got %ld from %ld\n",u-g,f-g);
    tr[++cnt] = u;
    u->siz = 1;
    u->ms = 0;
    for (Edge *e = u->e; e; e = e->e) if (e->v != f && !e->v->done) {
        dfs1(e->v, u);
        u->siz += e->v->siz;
        u->ms = std::max(u->ms, e->v->siz);
    }
}
Node *cent(Node *const u) {
    static int rsiz, i, x, usiz;
    static Node *res;
    cnt = 0;
    dfs1(u, NULL);
    usiz = u->siz;
    rsiz = u->ms;
    res = u;
    rep (i, 2, cnt) {
        x = std::max(tr[i]->ms, usiz - tr[i]->siz);
        if (x < rsiz)
            rsiz = x, res = tr[i];
    }
    return res;
}
ll dis(Node *const u, Node *const v) {
    static int l, r, k;
    l = u->etn;
    r = v->etn;
    if (l > r)
        std::swap(l, r);
    k = lg[r - l + 1];
    return u->dep + v->dep - 2 * std::min(st[k][l], st[k][r - (1 << k) + 1]);
}
Node *build(Node *u) {
    u = cent(u);
    u->done = true;
    Node *v;
    for (Edge *e = u->e; e; e = e->e) if (!e->v->done) {
        (v = build(e->v))->vfa = u;
        new VEdge(u, v, e->v);
    }
    return u;
}
Node *o;
void add(Node *const u, const int x) {
    static ll d;
    u->sw += x;
    for (o = u; o->vfa; o = o->vfa) {
        d = dis(u, o->vfa);
        o->sw0 += x;
        o->vfa->sw += x;
        o->sc0 += x * d;
        o->vfa->sc += x * d;
    }
}
ll calc(Node *const u) {
    static ll res;
    res = u->sc;
    for (o = u; o->vfa; o = o->vfa)
        res += o->vfa->sc - o->sc0 + dis(u, o->vfa) * (o->vfa->sw - o->sw0);
    return res;
}
ll query(Node *const u) {
    ll c = calc(u);
    for (VEdge *e = u->ve; e; e = e->e)
        if (calc(e->p) < c)
            return query(e->v);
    return c;
}
void init() {
    static int i, j;
    Node *rt = &g[1];
    dfs0(rt);
    rep (i, 2, etlen)
        lg[i] = lg[i >> 1] + 1;
    for (j = 1; (1 << j) <= etlen; ++j)
        for (i = 1; i + (1 << j) - 1 <= etlen; ++i)
            st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);

    vrt = build(rt);
}

int main() {
    static int m, i, u, v, w;
    n = io;
    m = io;
    re (i, 1, n) {
        u = io;
        v = io;
        w = io;
        new Edge(&g[u], &g[v], w);
        new Edge(&g[v], &g[u], w);
    }
    init();
    while (m--) {
        // printf("%d left\n", m);
        u = io;
        add(&g[u], (int)io);
        io.print(query(vrt));
    }

    io.flush();
    return 0;
}
