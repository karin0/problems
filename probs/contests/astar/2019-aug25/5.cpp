#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;

#ifdef AKARI
void cca() {
    std::cerr << "\033[39;0m" << std::endl;
}
template <typename T, typename... Arg
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", cca(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) rep(i, s_, t_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

const int N = 100003;

int n, bit[N], lg, tim;
inline void add(int i) {
    for (; i <= n; i += i & -i)
        ++bit[i];
}
inline void del(int i) {
    for (; i <= n; i += i & -i)
        --bit[i];
}
inline void add(int l, int r) {
    add(l);
    del(r + 1); // heiki
}
inline int qry(int i) {
    int res = 0;
    for (; i; i -= i & -i)
        res += bit[i];
    return res;
}

struct Seg *nil, *scurr;
struct Seg {
    Seg *lc, *rc;
    int cnt;
    Seg() {}
    Seg(int) : lc(nil), rc(nil), cnt(1) {}
    Seg(Seg *lc, Seg *rc) : lc(lc), rc(rc), cnt(lc->cnt + rc->cnt) {}
    Seg *insert(int i, int l, int r) const {
        if (l == r)
            return new (scurr++) Seg(1);
        int mid = (l + r) >> 1;
        if (i <= mid)
            return new (scurr++) Seg(lc->insert(i, l, mid), rc);
        else
            return new (scurr++) Seg(lc, rc->insert(i, mid + 1, r));
    }
    int qsum(int ql, int l, int r) const {
        if (ql <= l)
            return cnt;
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid)
            res = lc->qsum(ql, l, mid);
        res += rc->qsum(ql, mid + 1, r);
        return res;
    }
    int qsum(int ql, int qr, int l, int r) const {
        if (ql <= l && r <= qr)
            return cnt;
        int mid = (l + r) >> 1, res = 0;
        if (ql <= mid)
            res = lc->qsum(ql, qr, l, mid);
        if (qr > mid)
            res += rc->qsum(ql, qr, mid + 1, r);
        return res;
    }
} spool[N * 19], *segt[N];

struct Node {
    Node *jmp[19];
    int dfn, rdfn, dep;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *v, Edge *e) : v(v), e(e) {}
} pool[N << 1], *curr;
inline void arc(Node *u, Node *v) {
    u->e = new (curr++) Edge(v, u->e);
    v->e = new (curr++) Edge(u, v->e);
}
void dfs(Node *u, Node *fa) {
    u->jmp[0] = fa;
    int i = 0;
    while (u->jmp[i])
        u->jmp[i + 1] = u->jmp[i]->jmp[i], ++i;
    while (++i <= lg)
        u->jmp[i] = NULL;

    u->dfn = ++tim;
    segt[tim] = segt[tim - 1]->insert(u - g, 1, n);
    for (Edge *e = u->e; e; e = e->e) if (e->v != fa) {
        e->v->dep = u->dep + 1;
        dfs(e->v, u);
    }
    u->rdfn = tim;
}
int dis(Node *u, Node *v) {
    if (u == v)
        return 0;
    ccc(u, v);
    if (u->dep < v->dep)
        std::swap(u, v);
    Node *ou = u, *ov = v;
    ccc(ou-g, ov-g);
    ccc(u, v);
    per (i, lg, 0) {
        Node *t = u->jmp[i];
        if (t && t->dep >= v->dep) {
            u = t;
            if (u == v)
                return ou->dep - u->dep;
        }
    }
    if (u == v)
        return ou->dep - u->dep; // **
    per (i, lg, 0) {
        ccc(u-g, v-g);
        Node *tu = u->jmp[i], *tv = v->jmp[i];
        if (tu && tv && tu != tv)
            u = tu, v = tv;
    }
    ccc(u-g, v-g);
    ccc(ou-g, ov-g, u->jmp[0]-g);
    return ou->dep + ov->dep - (u->jmp[0]->dep << 1);
}
inline int cal(Node *r, Node *u) {
    return segt[r->rdfn]->qsum(u - g, 1, n) - segt[r->dfn - 1]->qsum(u - g, 1, n);
}
inline int cal(Node *u, int l, int r) {
    if (l > r)
        std::swap(l, r);
    return segt[u->rdfn]->qsum(l, r, 1, n) - segt[u->dfn - 1]->qsum(l, r, 1, n);
}
Node *dest, *lu;
int jump(Node *u) {
    lu = NULL;
    if (!qry(u->dfn))
        return dest = u, 0;
    Node *o = u;
    per (i, lg, 0) if (u->jmp[i] && qry(u->jmp[i]->dfn))
        u = u->jmp[i];
    dest = u->jmp[0];
    lu = u;
    // ccc(bool(dest), dest-g);
    if (!dest)
        return 0;
    return cal(u, o);
}

int main() {
    segt[0] = nil = spool;
    nil->lc = nil->rc = nil;
    int T;
    scanf("%d", &T);
    while (T--) {
        scurr = nil + 1;
        curr = pool;
        tim = 0;
        scanf("%d", &n);
        for (lg = 1; (1 << lg) <= n; ++lg);
        --lg;
        re (i, 1, n) {
            int u, v;
            scanf("%d%d", &u, &v);
            arc(&g[u], &g[v]);
        }
        Node *rt = &g[1];
        dfs(rt, NULL);
        int m;
        scanf("%d", &m);
        while (m--) {
            int op, u;
            scanf("%d%d", &op, &u);
            if (op == 1) {
                if (!qry(g[u].dfn))
                    add(g[u].dfn, g[u].rdfn);
            } else {
                int v;
                scanf("%d", &v);
                if (u == v) {
                    puts("0");
                    continue;
                }
                int ans = jump(&g[u]);
                if (!dest) {
                    printf("%d\n", std::abs(u - v));
                    continue;
                }
                Node *dlu = lu, *du = dest;
                ans += jump(&g[v]);
                if (lu && dlu == lu)
                    printf("%d\n", cal(lu, u, v) - 1); // ccc("QQ", dlu-g, lu-g);
                else
                    printf("%d\n", ans + dis(du, dest)); // ccc("HGG");
            }
        }

        if (T) rep(i, 1, n)
            bit[i] = 0, g[i].e = NULL;
    }
}