#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 100005, M = 200005;
int n;
struct Node {
    struct Edge *e;
    Node *fa, *hch, *top;
    int siz, dfn, dep;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
};
void dfs1(Node *u) {
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->e) {
        if ((v = e->v)->dep == 0) {
            v->dep = u->dep + 1;
            v->fa = u;
            dfs1(v);
            u->siz += v->siz;
            if (!u->hch || u->hch->siz <= v->siz)
                u->hch = v;
        }
    }
}
void dfs2(Node *u, Node *t) {
    static int tim = 0;
    u->dfn = ++tim;
    u->top = t;
    if (u->hch)
        dfs2(u->hch, t);
    for (Edge *e = u->e; e; e = e->e)
        if (e->v->fa == u && e->v != u->hch)
            dfs2(e->v, e->v);
}
struct P {
    int v;
    bool *c;
    bool operator < (const P &b) const {
        return v < b.v;
    }
};
struct SegT {
    int l, r;
    SegT *lc, *rc;
    std::priority_queue<P> h;
    SegT(int _l, int _r, SegT *_lc, SegT *_rc) : l(_l), r(_r), lc(_lc), rc(_rc) {}
    void hpop() {
        while (!h.empty() && !*h.top().c)
            h.pop();
    }
    void update(int ql, int qr, P v) {
        if (r < ql || qr < l)
            return;
        if (ql <= l && r <= qr) {
            hpop();
            h.push(v);
            return;
        }
        lc->update(ql, qr, v);
        rc->update(ql, qr, v);
    }
    int query(int qi) {
        // printf("q for %d\n", qi);
        if (r < qi || qi < l)
            return -1;
        hpop();
        int res = -1;
        if (l <= qi && qi <= r)
            res = h.empty() ? -1 : h.top().v;
        if (lc)
            res = std::max(res, std::max(lc->query(qi), rc->query(qi)));
        return res;
    }
} *segt;
SegT *build(int l, int r) {
    if (l == r)
        return new SegT(l, r, NULL, NULL);
    int mid = (l + r) >> 1;
    return new SegT(l, r, build(l, mid), build(mid + 1, r));
}
void init() {
    g[n].dep = 1;
    dfs1(&g[n]);
    dfs2(&g[n], &g[n]);
    segt = build(1, n);
}
struct Q {
    int a, b;
    bool operator < (const Q &o) const {
        return b < o.a;
    }
};
void update(Node *u, Node *v, P x) {
    static Q a[N];
    static int qcnt, i;
    qcnt = 0;
    a[++qcnt] = (Q){0, 0};
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        a[++qcnt] = (Q){u->top->dfn, u->dfn};
        u = u->top->fa;
    }
    if (u->dep < v->dep)
        std::swap(u, v);
    a[++qcnt] = (Q){v->dfn, u->dfn};
    a[++qcnt] = (Q){n + 1, n + 1};
    std::sort(a + 1, a + qcnt + 1);
    for (i = 2; i <= qcnt; ++i)
        segt->update(a[i - 1].b + 1, a[i].a - 1, x);
}
inline int query(Node *u) {
    return segt->query(u->dfn);
}
int main() {
    static int m, i, u, v, opt, x;
    static bool on[M];
    scanf("%d%d", &n, &m);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        new Edge(&g[u], &g[v]);
        new Edge(&g[v], &g[u]);
    }
    init();
    for (i = 1; i <= m; ++i) {
        scanf("%d", &opt);
        if (opt == 0) {
            on[i] = true;
            scanf("%d%d%d", &u, &v, &x);
            update(&g[u], &g[v], (P){x, &on[i]});
        } else if (opt == 1) {
            scanf("%d", &x);
            on[x] = false;
        } else {
            scanf("%d", &u);
            printf("%d\n", query(&g[u]));
        }
    }

    return 0;
}
