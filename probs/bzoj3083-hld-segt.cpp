#include <cstdio>
#include <climits>
#include <algorithm>
#include <new>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define news new (alloc(sizeof(SegT)))
#define newe new (alloc(sizeof(Edge)))
 
typedef unsigned int uint;
const int N = 100003;
const uint inf = UINT_MAX;
int n;
struct Node {
    uint x;
    int dfn, dep, siz;
    Node *fa, *top, *hch;
    struct Edge *e;
} g[N], *rt, *cap;
uint rdfn[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
};
struct SegT {
    SegT *lc, *rc;
    uint min, tag;
    SegT(SegT *_lc, SegT *_rc) : lc(_lc), rc(_rc), tag(0) {
        maintain();
    }
    void maintain() {
        if (lc)
            min = std::min(lc->min, rc->min);
    }
    void cover(const uint x) {
        min = tag = x;
    }
    void push_down() {
        if (tag && lc)
            lc->cover(tag), rc->cover(tag), tag = 0;
    }
    void update(int l, int r, int ql, int qr, uint x) {
        if (qr < ql)
            return;
        if (ql <= l && r <= qr) {
            cover(x);
            return;
        }
        int mid = (l + r) >> 1;
        push_down();
        if (ql <= mid)
            lc->update(l, mid, ql, qr, x);
        if (mid < qr)
            rc->update(mid + 1, r, ql, qr, x);
        maintain();
    }
    uint query(int l, int r, int ql, int qr) {
        if (qr < ql)
            return inf;
        if (ql <= l && r <= qr)
            return min;
        int mid = (l + r) >> 1;
        push_down();
        return std::min(ql <= mid ? lc->query(l, mid, ql, qr) : inf, mid < qr ? rc->query(mid + 1, r, ql, qr): inf);
    }
} *segt;
void *alloc(const size_t siz) {
    const static int S = N * 2 * sizeof(Edge) + N * 4 * sizeof(SegT);
    static char buf[S], *curr = buf, *p;
    if (curr + siz > buf + S)
        return malloc(siz);
    p = curr;
    curr += siz;
    return p;
}
SegT *build(int l, int r) {
    if (l == r) {
        SegT *o = news SegT(NULL, NULL);
        o->min = rdfn[l];
        return o;
    }
    int mid = (l + r) >> 1;
    return news SegT(build(l, mid), build(mid + 1, r));
}
void dfs1(Node *u) {
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->e) if (!(v = e->v)->siz) {
        v->dep = u->dep + 1;
        v->fa = u;
        dfs1(v);
        u->siz += v->siz;
        if (!u->hch || v->siz > u->hch->siz)
            u->hch = v;
    }
}
void dfs2(Node *u, Node *t) {
    static int tim;
    u->dfn = ++tim;
    rdfn[tim] = u->x;
    u->top = t;
    if (u->hch)
        dfs2(u->hch, t);
    for (Edge *e = u->e; e; e = e->e)
        if (!e->v->dfn && e->v != u->hch)
            dfs2(e->v, e->v);
}
void hld_init() {
    rt->dep = 1;
    dfs1(rt);
    dfs2(rt, rt);
    segt = build(1, n);
}
void update(Node *u, Node *v, uint x) {
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        segt->update(1, n, u->top->dfn, u->dfn, x);
        u = u->top->fa;
    }
    if (u->dep < v->dep)
        std::swap(u, v);
    segt->update(1, n, v->dfn, u->dfn, x);
}
Node *lca(Node *u, Node *v) {
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        u = u->top->fa;
    }
    if (u->dep < v->dep)
        std::swap(u, v);
    return v;
}
uint query(Node *u) {
    static Node *p;
    if (u == cap)
        return segt->query(1, n, 1, n);
    if (rt == cap)
        return segt->query(1, n, u->dfn, u->dfn + u->siz - 1);
    for (p = cap; p; p = p->top->fa) {
        if (p->top->fa == u) {
            p = p->top;
            break;
        }
        if (p->top == u->top) {
            p = p->dep > u->dep ? u->hch : NULL;
            break;
        }
    }
    return p ? std::min(segt->query(1, n, 1, p->dfn - 1), segt->query(1, n, p->dfn + p->siz, n))
             : segt->query(1, n, u->dfn, u->dfn + u->siz - 1);
}
 
int main() {
    static int m, i, u, v, opt;
    static uint x;
    scanf("%d%d", &n, &m);
    re (i, 1, n) {
        scanf("%d%d", &u, &v);
        newe Edge(&g[u], &g[v]);
        newe Edge(&g[v], &g[u]);
    }
    rep (i, 1, n)
        scanf("%u", &g[i].x);
    scanf("%d", &u), cap = rt = &g[u];
    hld_init();
    while (m--) {
        scanf("%d", &opt);
        if (opt == 2)
            scanf("%d%d%u", &u, &v, &x), update(&g[u], &g[v], x);
        else {
            scanf("%d", &u);
            if (opt == 1)
                cap = &g[u];
            else
                printf("%u\n", query(&g[u]));
        }
    }
    return 0;
}
