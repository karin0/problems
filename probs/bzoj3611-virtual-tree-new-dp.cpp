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
            fwrite(p = b, 1, L, stdout);
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
const int N = 1000003, inf = 0x3f3f3f3f;
int n, m, etlen, lg[N * 2]; // *****
struct Node {
    int dfn, etn, dep, fcnt, fmn, fmx;
    bool cap, vis;
    struct Edge *e;
    struct VEdge *ve;
} g[N], *st[21][N * 2], *rt = &g[1];
// *** log_2 (2n) !!
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
    void *operator new (size_t) {
        static Edge pool[N * 4], *curr = pool;
        return curr++;
    }
};
void dfs(Node *u) {
    static int tim = 0;
    // printf("%ld here, et = %d\n", u-g, etlen);
    st[0][u->etn = ++etlen] = u;
    u->dfn = ++tim;
    for (Edge *e = u->e; e; e = e->e) if (!e->v->etn) {
        e->v->dep = u->dep + 1;
        dfs(e->v);
        st[0][++etlen] = u;
    }
}
inline Node *min(Node *u, Node *v) {
    return u->dep < v->dep ? u : v;
}
Node *lca(Node *u, Node *v) {
    static int l, r, k;
    l = u->etn;
    r = v->etn;
    if (l > r)
        std::swap(l, r);
    k = lg[r - l + 1];
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}
struct VEdge {
    Node *v;
    VEdge *e;
    int w;
    VEdge() {}
    VEdge(Node *_u, Node *_v) : v(_v), e(_u->ve), w(_v->dep - _u->dep) {
        if (_u != _v)
            _u->ve = this; // printf("Add %ld  to %ld\n",_u-g,_v-g);
        // printf("Connect %ld to %ld\n", _u-g, _v-g);
    }
};
namespace vtr {
    int k;
    VEdge pool[N], *curr;
    inline bool cmp(const Node *u, const Node *v) {
        return u->etn < v->etn;
    }
    ll fsum, t;
    int fmx, fmn;
    void dfs0(Node *u) {
        if (u->cap) {
            u->fcnt = 1;
            u->fmn = u->fmx = 0;
        } else {
            u->fcnt = 0;
            u->fmn = inf;
            u->fmx = -inf;
        }
        for (VEdge *e = u->ve; e; e = e->e) {
            dfs0(e->v);
            u->fcnt += e->v->fcnt;
        }
    }
    void crash(Node *u) {
        for (VEdge *e = u->ve; e; e = e->e) 
            crash(e->v);
        u->ve = NULL;
        u->cap = false;
    }
    inline void chmin(int &fir, int &sec, const int v) {
        if (v < fir)
            sec = fir, fir = v;
        else if (v < sec)
            sec = v;
    }
    inline void chmax(int &fir, int &sec, const int v) {
        if (v > fir)
            sec = fir, fir = v;
        else if (v > sec)
            sec = v;
    }
    void dfs1(Node *u) {
        int secmn = inf, secmx = -inf;
        for (VEdge *e = u->ve; e; e = e->e) {
            t = e->v->fcnt;
            fsum += (ll)t * (k - t) * e->w;
            dfs1(e->v);
            chmin(u->fmn, secmn, e->v->fmn + e->w);
            chmax(u->fmx, secmx, e->v->fmx + e->w);
        }
        fmn = std::min(fmn, u->fmn + secmn);
        fmx = std::max(fmx, u->fmx + secmx);
    }
    void calc(Node *a[], const int _k) {
        static Node *sta[N], *l, *u;
        static int top, i;
        k = _k;
        fsum = 0;
        fmn = inf;
        fmx = -inf;
        curr = pool;
        rep (i, 1, k)
            a[i]->cap = true;
        sta[top = 1] = rt;
        std::sort(a + 1, a + k + 1, cmp);
        rep (i, 1, k) {
            u = a[i];
            l = lca(u, sta[top]);
            while (top >= 2 && l->dep < sta[top]->dep) {
                if (l->dep >= sta[top - 1]->dep) {
                    new (curr++) VEdge(l, sta[top--]);
                    if (sta[top] != l)
                        sta[++top] = l;
                    break;
                }
                new (curr++) VEdge(sta[top - 1], sta[top]);
                --top;
            }
            if (sta[top] != u)
                sta[++top] = u;
        }
        re (i, 1, top)
            new (curr++) VEdge(sta[i], sta[i + 1]);
        
        dfs0(rt);
        dfs1(rt);
        crash(rt); // *****
    }
}
void init() {
    static int i, j;
    dfs(rt);
    rep (i, 2, etlen)
        lg[i] = lg[i >> 1] + 1;
    for (j = 1; (1 << j) <= etlen; ++j)
        for (i = 1; i + (1 << j) - 1 <= etlen; ++i) // ***
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
}
int main() {
    static int i, k, u, v;
    static Node *a[N];
    n = io;
    re (i, 1, n) {
        u = io;
        v = io;
        new Edge(&g[u], &g[v]);
        new Edge(&g[v], &g[u]);
    }
    init();
    m = io;
    while (m--) {
        // printf("%d left\n", m);
        k = io;
        rep (i, 1, k)
            a[i] = &g[(int)io];
        vtr::calc(a, k);
        io.print(vtr::fsum, false);
        io.pc(' ');
        io.print(vtr::fmn, false);
        io.pc(' ');
        io.print(vtr::fmx);
    }

    io.flush();
    return 0;
}
