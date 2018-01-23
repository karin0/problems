#include <cstdio>
#include <algorithm>

const int MAXN = 30005, MAXM = 100005, MAXQ = 40005;
int n;
struct Pair {
    int u, v; // u < v
    bool removed, in_tree;
} se[MAXM];
bool operator < (const Pair &a, const Pair &b) {
    return a.u < b.u || (a.u == b.u && a.v < b.v);
}
struct Query {
    int opt, u, v, ans;
} qwq[MAXQ];
struct Node {
    struct Edge *adj;
    Node *fa, *hch, *top;
    int siz, dfn, dep;
} g[MAXN];
struct Edge {
    Node *v;
    Edge *next;
    Edge(Node *u, Node *_v) : v(_v), next(u->adj) {}
};
void arc(Node *u, Node *v) {
    u->adj = new Edge(u, v);
}
void dfs1(Node *u) {
    Node *v;
    u->siz = 1;
    for (Edge *e = u->adj; e; e = e->next) {
        v = e->v;
        if (!v->siz) {
            v->fa = u;
            v->dep = u->dep + 1;
            dfs1(v);
            u->siz += v->siz;
            if (!u->hch || v->siz > u->hch->siz)
                u->hch = v;
        }
    }
}
void dfs2(Node *u, Node *top) {
    static int tim = 0;
    u->dfn = ++tim;
    u->top = top;
    if (u->hch)
        dfs2(u->hch, top);
    Node *v;
    for (Edge *e = u->adj; e; e = e->next) {
        v = e->v;
        if (v->fa == u && v != u->hch)
            dfs2(v, v);
    }
}
struct Seg {
    int l, r;
    Seg *lc, *rc;
    int cnt;
    bool tag;
    Seg(int _l, int _r, Seg *_lc, Seg *_rc) : l(_l), r(_r), lc(_lc), rc(_rc) {
        cnt = r - l + 1;
    }
    void cover() {
        cnt = 0;
        tag = true;
    }
    void push_down() {
        if (tag && lc)
            lc->cover(), rc->cover(), tag = 0;
    }
    void update(const int ql, const int qr) {
        if (qr < l || r < ql)
            return;
        if (ql <= l && r <= qr) {
            cover();
            return;
        }
        push_down();
        lc->update(ql, qr);
        rc->update(ql, qr);
        cnt = lc->cnt + rc->cnt;
    }
    int query(const int ql, const int qr) {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return cnt;
        push_down();
        return lc->query(ql, qr) + rc->query(ql, qr);
    }
} *segt;
Seg *build(const int l, const int r) {
    if (l == r)
        return new Seg(l, l, NULL, NULL);
    int mid = (l + r) >> 1;
    return new Seg(l, r, build(l, mid), build(mid + 1, r));
}
void hld_init() {
    g[1].dep = 1; // **
    dfs1(g + 1);
    dfs2(g + 1, g + 1); // **
    segt = build(1, n);
}
void unite(Node *u, Node *v) {
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        segt->update(u->top->dfn, u->dfn);
        u = u->top->fa;
    }
    if (u == v)
        return;
    if (u->dep < v->dep)
        std::swap(u, v);
    segt->update(v->hch->dfn, u->dfn);
}
int query(Node *u, Node *v) {
    static int res;
    res = 0;
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        res += segt->query(u->top->dfn, u->dfn);
        u = u->top->fa;
    }
    if (u == v)
        return res;
    if (u->dep < v->dep)
        std::swap(u, v);
    return res + segt->query(v->hch->dfn, u->dfn);
}
struct DisjointSet {
    int fa[MAXN];
    void init(int bound) {
        for (int i = 1; i <= bound; ++i)
            fa[i] = i;
    }
    int find(int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        fa[find(x)] = find(y);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
} ds;

int main() {
    static int m, i, u, v, opt, qcnt;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        if (u > v)
            std::swap(u, v);
        se[i].u = u, se[i].v = v;
    }
    std::sort(se + 1, se + m + 1);
    for (qcnt = 1; ; ++qcnt) {
        scanf("%d", &opt);
        if (opt == -1)
            break;
        Query &q = qwq[qcnt];
        q.opt = opt;
        scanf("%d%d", &u, &v);
        q.u = u, q.v = v;
        if (opt == 0) {
            if (u > v)
                std::swap(u, v);
            std::lower_bound(se + 1, se + m + 1, (Pair){u, v})->removed = true;
        }
    }
    --qcnt;
    ds.init(n);
    for (i = 1; i <= m; ++i) {
        Pair &e = se[i];
        if (e.removed || ds.same(e.u, e.v))
            continue;
        arc(g + e.u, g + e.v), arc(g + e.v, g + e.u);
        ds.unite(e.u, e.v);
        e.in_tree = true;
    }
    hld_init();
    for (i = 1; i <= m; ++i) {
        Pair &e = se[i];
        // printf("%d -> %d : %d, %d\n", e.u, e.v, e.removed, e.in_tree);
        if (e.removed || e.in_tree)
            continue;
        unite(g + e.u, g + e.v);
    }
    for (i = qcnt; i >= 1; --i) { // 
        Query &q = qwq[i];
        if (q.opt == 0)
            unite(g + q.u, g + q.v);
        else
            q.ans = query(g + q.u, g + q.v);
    }
    for (i = 1; i <= qcnt; ++i) {
        Query &q = qwq[i];
        if (q.opt == 1)
            printf("%d\n", q.ans);
    }

    return 0;
}
