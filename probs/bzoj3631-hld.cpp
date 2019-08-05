#include <cstdio>
#include <algorithm>

typedef long long ll;
const int MAXN = 300005;
int n;
struct Node {
    struct Edge *adj;
    Node *fa, *hch, *top;
    int siz, dfn, dep;
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
    int lb, rb, len;
    Seg *lc, *rc;
    // -1：空 Tag
    ll sum, tag;
    Seg(const int lb, const int rb, Seg *lc, Seg *rc) : lb(lb), rb(rb), lc(lc), rc(rc), sum(0), tag(0) {}
    void cover(int x) {
        sum += x * (rb - lb + 1);
        tag += x;
    }
    void push_down() {
        if (tag != 0 && lc) {
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
    }
    void update(const int l, const int r, const int x) {
        if (lb > r || rb < l)
            return;
        if (l <= lb && rb <= r) {
            cover(x);
            return;
        }
        push_down();
        lc->update(l, r, x);
        rc->update(l, r, x);
        sum = lc->sum + rc->sum;
    }
    ll query(const int l) {
        if (lb == rb)
            return sum;
        push_down();
        int mid = (lb + rb) >> 1;
        if (l <= mid)
            return lc->query(l);
        else
            return rc->query(l);
    }
} *segt;
Seg *build(const int l, const int r) {
    if (l == r)
        return new Seg(l, l, NULL, NULL);
    int mid = (l + r) >> 1;
    return new Seg(l, r, build(l, mid), build(mid + 1, r));
}
void init() {
    g[1].dep = 1;
    dfs1(g + 1);
    dfs2(g + 1);
    segt = build(1, n);
}
void update(Node *u, Node *v) {
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        segt->update(u->top->dfn, u->dfn, 1);
        u = u->top->fa;
    }
    if (u->dep < v->dep)
        std::swap(u, v);
    segt->update(v->dfn, u->dfn, 1);
}

int main() {
    static int i, u, v, route[MAXN];
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%d", route + i);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        arc(g + u, g + v);
        arc(g + v, g + u);
    }
    init();
    for (i = 1; i < n; ++i) {
        update(g + route[i], g + route[i + 1]);
        segt->update(g[route[i + 1]].dfn, g[route[i + 1]].dfn, -1);
    }
    for (i = 1; i <= n; ++i)
        printf("%lld\n", segt->query(g[i].dfn));
    return 0;
}
