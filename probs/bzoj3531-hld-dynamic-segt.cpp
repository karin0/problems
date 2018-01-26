#include <cstdio>
#include <algorithm>

const int N = 100005;
struct Node {
    struct Edge *e;
    int w, c;
    int dep, siz, dfn;
    Node *fa, *top, *hch;
} g[N];
struct Edge {
    Node *v;
    Edge *next;
    Edge(Node *_u, Node *_v) : v(_v), next(_u->e) {
        _u->e = this;
    }
};
int n;
struct SegT {
    SegT *lc, *rc;
    int l, r, sum, max;
    SegT(int _l, int _r) : l(_l), r(_r) {}
    void maintain() {
        sum = (lc ? lc->sum : 0) + (rc ? rc->sum : 0);
        max = std::max(lc ? lc->max : 0, rc ? rc->max : 0);
    }
    void update(int qi, int x) {
        if (l == r) {
            sum = max = x;
            return;
        }
        int mid = (l + r) >> 1;
        if (qi <= mid) {
            if (!lc)
                lc = new SegT(l, mid);
            lc->update(qi, x);
        } else {
            if (!rc)
                rc = new SegT(mid + 1, r);
            rc->update(qi, x);
        }
        maintain();
    }
    int query_sum(int ql, int qr) {
        if (ql <= l && r <= qr)
            return sum;
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid && lc)
            res += lc->query_sum(ql, qr);
        if (qr > mid && rc)
            res += rc->query_sum(ql, qr);
        return res;
    }
    int query_max(int ql, int qr) {
        if (ql <= l && r <= qr)
            return max;
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid && lc)
            res = std::max(res, lc->query_max(ql, qr));
        if (qr > mid && rc)
            res = std::max(res, rc->query_max(ql, qr));
        return res;
    }
} *segt[N];
SegT *init(SegT *&o) {
    if (!o)
        o = new SegT(1, n);
    return o;
}
namespace hld {
    void dfs1(Node *u) {
        u->siz = 1;
        for (Edge *e = u->e; e; e = e->next) {
            Node *v = e->v;
            if (v == u->fa)
                continue;
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
        u->dfn = ++tim;
        u->top = t;
        if (u->hch)
            dfs2(u->hch, t);
        for (Edge *e = u->e; e; e = e->next) {
            Node *v = e->v;
            if (v != u->hch && v->fa == u)
                dfs2(v, v);
        }
    }
    void init() {
        g[1].dep = 1;
        dfs1(&g[1]);
        dfs2(&g[1], &g[1]);
    }
    int query_sum(Node *u, Node *v) {
        int res = 0, c = u->c;
        while (u->top != v->top) {
            if (u->top->dep < v->top->dep)
                std::swap(u, v);
            res += segt[c]->query_sum(u->top->dfn, u->dfn);
            u = u->top->fa;
        }
        if (u->dep < v->dep)
            std::swap(u, v);
        res += segt[c]->query_sum(v->dfn, u->dfn);
        return res;
    }
    int query_max(Node *u, Node *v) {
        int res = 0, c = u->c;
        while (u->top != v->top) {
            if (u->top->dep < v->top->dep)
                std::swap(u, v);
            res = std::max(res, segt[c]->query_max(u->top->dfn, u->dfn));
            u = u->top->fa;
        }
        if (u->dep < v->dep)
            std::swap(u, v);
        res = std::max(res, segt[c]->query_max(v->dfn, u->dfn));
        return res;
    }
}

int main() {
    static int m, i, u, v;
    static char opt[5];
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d%d", &g[i].w, &g[i].c);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        new Edge(&g[u], &g[v]);
        new Edge(&g[v], &g[u]);
    }
    hld::init();
    for (i = 1; i <= n; ++i) {
        init(segt[g[i].c]);
        segt[g[i].c]->update(g[i].dfn, g[i].w);
    }
    while (m--) {
        scanf("%s%d%d", opt, &u, &v);
        if (opt[0] == 'C') {
            if (opt[1] == 'C') {
                segt[g[u].c]->update(g[u].dfn, 0);
                g[u].c = v;
                init(segt[v])->update(g[u].dfn, g[u].w);
            } else {
                segt[g[u].c]->update(g[u].dfn, v);
                g[u].w = v;
            }
        } else
            printf("%d\n", (opt[1] == 'S') ? hld::query_sum(&g[u], &g[v]) : hld::query_max(&g[u], &g[v]));

    }

    return 0;
}
