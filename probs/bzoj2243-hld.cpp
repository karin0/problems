#include <cstdio>
#include <algorithm>

const int MAXN = 500005;
int n, ecnt;
struct Node {
    struct Edge *adj;
    Node *fa, *hch, *top;
    int siz, dfn, dep, col;
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
    // -1：空 Tag
    int cnt, lcol, rcol, tag;
    Seg(const int lb, const int rb, Seg *lc, Seg *rc) : lb(lb), rb(rb), lc(lc), rc(rc), tag(-1) {
        if (lb == rb)
            cnt = 1, lcol = rcol = rdfn[lb]->col;
        else {
            cnt = lc->cnt + rc->cnt - (lc->rcol == rc->lcol);
            lcol = lc->lcol;
            rcol = rc->rcol;
        }
        // printf("[%d, %d] (%d to %d) cnt = %d\n", lb, rb, rdfn[lb] - g, rdfn[rb] - g, cnt);
    }
    void cover(const int x) {
        cnt = 1;
        lcol = rcol = tag = x;
    }
    void push_down() {
        if (tag == -1)
            return;
        if (lc)
            lc->cover(tag);
        if (rc)
            rc->cover(tag);
        tag = -1;
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
        cnt = lc->cnt + rc->cnt - (lc->rcol == rc->lcol);
        lcol = lc->lcol;
        rcol = rc->rcol;
    }
    int query(const int l, const int r) {
        if (lb > r || rb < l)
            return 0;
        if (l <= lb && rb <= r)
            return cnt;
        push_down();
        int resa = lc->query(l, r), resb = rc->query(l, r);
        if (resa > 0 && resb > 0)
            resa -= (lc->rcol == rc->lcol);
        return resa + resb;
    }
    int query_col(const int x) {
        if (lb == rb)
            return lcol;
        push_down();
        int mid = (lb + rb) >> 1;
        if (x <= mid)
            return lc->query_col(x);
        else
            return rc->query_col(x);
    }
} *segt;
Seg *build(const int l, const int r) {
    if (l == r)
        return new Seg(l, r, NULL, NULL);
    int mid = (l + r) >> 1;
    return new Seg(l, r, build(l, mid), build(mid + 1, r));
}
void init() {
    g[1].dep = 1;
    dfs1(g + 1);
    dfs2(g + 1);
    segt = build(1, n);
}

int query(Node *u, Node *v) {
    static int ucnt, utc, vcnt, vtc, rcnt, rtc;
    if (u->top->dep < v->top->dep)
        std::swap(u, v);
    if (u->top == v->top)
        return segt->query(v->dfn, u->dfn); // 特判！
    ucnt = segt->query(u->top->dfn, u->dfn);
    utc = segt->query_col(u->top->dfn);
    vcnt = segt->query(v->top->dfn, v->dfn);
    vtc = segt->query_col(v->top->dfn);
    u = u->top->fa;
    v = v->top->fa;
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v), std::swap(ucnt, vcnt), std::swap(utc, vtc);
        rcnt = segt->query(u->top->dfn, u->dfn);
        rtc = segt->query_col(u->dfn);
        ucnt += rcnt - (utc == rtc);
        utc = segt->query_col(u->top->dfn);
        u = u->top->fa;
    }
    if (u->dep < v->dep) // not the top!
        std::swap(u, v), std::swap(ucnt, vcnt), std::swap(utc, vtc);
    rcnt = segt->query(v->dfn, u->dfn);
    rtc = segt->query_col(u->dfn);
    ucnt += rcnt - (utc == rtc);
    utc = segt->query_col(v->dfn);
    return ucnt + vcnt - (utc == vtc);
}
void update(Node *u, Node *v, const int c) {
    if (u->top->dep < v->top->dep)
        std::swap(u, v);
    if (u->top == v->top) {
        segt->update(v->dfn, u->dfn, c); // 特判！
        return;
    }
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        segt->update(u->top->dfn, u->dfn, c);
        u = u->top->fa;
    }
    if (u->dep < v->dep)
        std::swap(u, v);
    segt->update(v->dfn, u->dfn, c);
}
/*
Node* lca(Node *u, Node *v) {
    while (u->top != v->top) {
        if (u->top->dep < v->top->dep)
            std::swap(u, v);
        u = u->top->fa;
    }
    if (u->top->dep < v->top->dep)
        std::swap(u, v);
    return v;
}
void update_to(Node *u, Node *tar, const int c) {
    Node *t = tar->top;
    while (u->top != t) {
        segt->update(u->top->dfn, u->dfn, c);
        u = u->top->fa;
    }
    segt->update(tar->dfn, u->dfn, c);
    }
*/

int main() {
    static int m, i, u, v, x;
    static char opt[30];
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", &g[i].col);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        arc(g + u, g + v);
        arc(g + v, g + u);
    }
    init();
    for (i = 1; i <= m; ++i) {
        scanf("%s%d%d", opt, &u, &v);
        if (opt[0] == 'Q') {
            printf("%d\n", query(g + u, g + v));
        } else {
            scanf("%d", &x);
            update(g + u, g + v, x);
        }
    }
    return 0;
}
