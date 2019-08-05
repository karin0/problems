#include <cstdio>

typedef long long ll;
const int MAXN = 100005;
int n, ecnt;
struct Node {
    struct Edge *adj;
    Node *fa, *hch, *top;
    int siz, dfn;
    ll val;
} g[MAXN], *rdfn[MAXN];
struct Edge {
    Node *v;
    Edge *next;
    Edge(Node *u, Node *v) : v(v), next(u->adj) {}
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
            dfs1(v);
            u->siz += v->siz;
            if (!u->hch || v->siz > u->hch->siz)
                u->hch = v;
        }
    }
}
void dfs2(Node *u) {
    static int tim = 0;
    u->dfn = ++tim;
    rdfn[tim] = u;
    if (!u->fa || u != u->fa->hch)
        u->top = u;
    else
        u->top = u->fa->top;
    if (u->hch)
        dfs2(u->hch);
    Node *v;
    for (Edge *e = u->adj; e; e = e->next) {
        v = e->v;
        if (v->fa == u && v != u->hch)
            dfs2(v);
    }
}
struct Seg {
    int lb, rb;
    Seg *lc, *rc;
    ll sum, tag;
    Seg(const int lb, const int rb, Seg *lc, Seg *rc, const ll sum) : lb(lb), rb(rb), lc(lc), rc(rc), sum(sum), tag(0) {}
    void cover(const ll x) { // 当前节点对应区间内各点加
        sum += x * (rb - lb + 1);
        tag += x;
    }
    void push_down() {
        if (!tag)
            return;
        if (lc)
            lc->cover(tag);
        if (rc)
            rc->cover(tag);
        tag = 0;
    }
    void update(const int l, const int r, const ll x) {
        if (lb > r || rb < l)
            return;
        if (l <= lb && rb <= r) {
            cover(x);
            return;
        }
        push_down();
        sum = 0;
        //if (lc)
            lc->update(l, r, x), sum += lc->sum;
        //if (rc)
            rc->update(l, r, x), sum += rc->sum;
    }
    ll query(const int l, const int r) {
        if (lb > r || rb < l)
            return 0;
        if (l <= lb && rb <= r)
            return sum;
        push_down();
        ll res = 0;
        //if (lc)
            res += lc->query(l, r); // instead of `lc->sum;`
        //if (rc)
            res += rc->query(l, r);
        return res;
    }
} *segt;
Seg *build(const int l, const int r) {
    if (l == r)
        return new Seg(l, r, NULL, NULL, rdfn[l]->val);
    int mid = (l + r) >> 1;
    Seg *lc = build(l, mid), *rc = build(mid + 1, r);
    return new Seg(l, r, lc, rc, lc->sum + rc->sum);
}
void init() {
    dfs1(g + 1);
    dfs2(g + 1);
    segt = build(1, n);
}
void update(const Node *u, const ll x) {
    segt->update(u->dfn, u->dfn, x);
}
void update_subtree(const Node *u, const ll x) {
    segt->update(u->dfn, u->dfn + u->siz - 1, x);
}
ll query_to_root(const Node *u) {
    static ll res;
    res = 0;
    while (u) {
        res += segt->query(u->top->dfn, u->dfn);
        u = u->top->fa;
    }
    return res;
}

int main() {
    static int m, i, u, v, x, opt;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%lld", &g[i].val);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        arc(g + u, g + v);
        arc(g + v, g + u);
    }
    init();
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &opt, &u);
        if (opt == 3) {
            printf("%lld\n", query_to_root(g + u));
        } else {
            scanf("%d", &x);
            if (opt == 1)
                update(g + u, x);
            else
                update_subtree(g + u, x);
        }
    }
    return 0;
}
