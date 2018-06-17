#include <cstdio>
#include <climits>
#include <algorithm>

typedef long long ll;
const int MAXN = 30005;
int n, ecnt;
struct Node {
    struct Edge *adj;
    Node *fa, *hch, *top;
    int siz, dfn, dep, val;
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
            v->dep = u->dep + 1;
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
    int sum, max;
    Seg(const int lb, const int rb, Seg *lc, Seg *rc) : lb(lb), rb(rb), lc(lc), rc(rc) {
        if (lb == rb)
            sum = max = rdfn[lb]->val;
        else {
            sum = lc->sum + rc->sum;
            max = std::max(lc->max, rc->max);
        }
    }
    void update(const int l, const int x) {
        if (lb == rb) {
            sum = max = x;
            return;
        }
        int mid = (lb + rb) >> 1;
        if (l <= mid)
            lc->update(l, x);
        else
            rc->update(l, x);
        sum = lc->sum + rc->sum;
        max = std::max(lc->max, rc->max);
    }
    int query_sum(const int l, const int r) {
        if (lb > r || rb < l)
            return 0;
        if (l <= lb && rb <= r)
            return sum;
        return lc->query_sum(l, r) + rc->query_sum(l, r);
    }
    int query_max(const int l, const int r) {
        if (lb > r || rb < l)
            return INT_MIN;
        if (l <= lb && rb <= r)
            return max;
        return std::max(lc->query_max(l, r), rc->query_max(l, r));
    }
} *segt;
Seg *build(const int l, const int r) {
    if (l == r)
        return new Seg(l, r, NULL, NULL);
    int mid = (l + r) >> 1;
    Seg *lc = build(l, mid), *rc = build(mid + 1, r);
    return new Seg(l, r, lc, rc);
}
void init() {
    g[1].dep = 1;
    dfs1(g + 1);
    dfs2(g + 1);
    segt = build(1, n);
}
void update(const Node *u, const int x) {
    segt->update(u->dfn, x);
}
int query_sum(Node *u, Node *v) {
    static int res;
    res = 0;
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        res += segt->query_sum(u->top->dfn, u->dfn);
        u = u->top->fa;
    }
    if (u->dep < v->dep)
        std::swap(u, v);
    res += segt->query_sum(v->dfn, u->dfn);
    return res;
}
int query_max(Node *u, Node *v) {
    static int res;
    res = INT_MIN;
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        res = std::max(res, segt->query_max(u->top->dfn, u->dfn));
        u = u->top->fa;
    }
    if (u->dep < v->dep)
        std::swap(u, v);
    res = std::max(res, segt->query_max(v->dfn, u->dfn));
    return res;
}

int main() {
    static int m, i, u, v;
    static char opt[20];
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        arc(g + u, g + v);
        arc(g + v, g + u);
    }
    for (i = 1; i <= n; ++i)
        scanf("%d", &g[i].val);
    init();
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        scanf("%s%d%d", opt, &u, &v);
        if (opt[1] == 'H')
            update(g + u, v);
        else if (opt[1] == 'M')
            printf("%d\n", query_max(g + u, g + v));
        else
            printf("%d\n", query_sum(g + u, g + v));
    }
    return 0;
}
