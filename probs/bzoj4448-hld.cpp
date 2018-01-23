#include <cstdio>
#include <algorithm>

const int N = 200003;
int n;
struct Node {
    struct Edge *e;
    Node *fa, *hch, *top;
    int siz, dfn, dep;
} g[N];
struct Edge {
    Node *v;
    Edge *next;
    Edge(Node *_u, Node *_v) : v(_v), next(_u->e) {
        _u->e = this;
    }
};
void dfs1(Node *u) {
    u->siz = 1;
    Node *v;
    for (Edge *e = u->e; e; e = e->next) {
        v = e->v;
        v->fa = u;
        v->dep = u->dep + 1;
        dfs1(v);
        u->siz += v->siz;
        if (!u->hch || v->siz > u->hch->siz)
            u->hch = v;
    }
}
void dfs2(Node *u, Node *t) {
    static int tim = 0;
    u->dfn = ++tim;
    u->top = t;
    if (u->hch)
        dfs2(u->hch, t);
    Node *v;
    for (Edge *e = u->e; e; e = e->next) {
        v = e->v;
        if (v != u->hch)
            dfs2(v, v);
    }
}
struct Seg {
    int l, r;
    Seg *fa, *lc, *rc;
    int sum;
    Seg (int _l, int _r, Seg *_lc, Seg *_rc) : l(_l), r(_r), lc(_lc), rc(_rc) {
        if (lc)
            lc->fa = rc->fa = this;
    }
    int query(const int ql, const int qr) {
        if (qr < l || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return sum;
        return lc->query(ql, qr) + rc->query(ql, qr);
    }
} *segt, *leaf[N];
Seg *build(const int l, const int r) {
    if (l == r)
        return leaf[l] = new Seg(l, l, NULL, NULL);
    int mid = (l + r) >> 1;
    return new Seg(l, r, build(l, mid), build(mid + 1, r));
}
void add(const int i, const int x) {
    static Seg *o;
    for (o = leaf[i]; o; o = o->fa)
        o->sum += x;
}
Node *rt;
void hld_init() {
    rt->dep = 1;
    dfs1(rt);
    dfs2(rt, rt);
    segt = build(1, n);
}
int ret_dis, ret_res;
void query(Node *u, Node *v) {
    Node *ou = u, *ov = v;
    ret_res = 0;
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        ret_res += segt->query(u->top->dfn, u->dfn);
        u = u->top->fa;
    }
    if (u->dep < v->dep) // ***
        std::swap(u, v);
    ret_res += segt->query(v->dfn, u->dfn);
    ret_dis = ou->dep + ov->dep - v->dep * 2 + 1;
}
void update(Node *u, const int x) {
    add(u->dfn, x);
}

struct Query {
    int opt, u, v, t, tim;
    bool operator < (const Query &o) const {
        return (t < o.t) || (t == o.t && opt < o.opt); // **
    }
} qwq[N];
int main() {
    static int m, i, u, c, ans1[N], ans2[N];
    static bool isq[N];
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d", &u);
        if (u)
            new Edge(g + u, g + i);
        else
            rt = g + i;
    }
    hld_init();
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) {
        Query &q = qwq[i];
        q.tim = i;
        scanf("%d%d", &q.opt, &q.u);
        if (q.opt == 1) {
            scanf("%d%d", &q.v, &c);
            q.t = i - c;
        } else
            q.t = i;
    }
    std::sort(qwq + 1, qwq + m + 1);
    for (i = 1; i <= m; ++i) {
        Query &q = qwq[i];
        if (q.opt == 1) {
            query(g + q.u, g + q.v);
            ans1[q.tim] = ret_dis;
            ans2[q.tim] = ret_res;
            isq[q.tim] = true;
        } else
            update(g + q.u, 1);
    }
    for (i = 1; i <= m; ++i)
        if (isq[i])
            printf("%d %d\n", ans1[i], ans2[i]);

    return 0;
}
