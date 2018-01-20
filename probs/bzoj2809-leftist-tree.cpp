#include <cstdio>
#include <algorithm>

typedef long long ll;
const int N = 100005;

struct LT {
    LT *lc, *rc;
    int x, d, siz;
    ll sum;
    LT(int _x) : x(_x), siz(1), sum(_x) {}
    void maintain() {
        siz = (lc ? lc->siz : 0) + (rc ? rc->siz : 0) + 1;
        sum = (lc ? lc->sum : 0) + (rc ? rc->sum : 0) + x;
    }
};
LT *merge(LT *a, LT *b) {
    if (!a)
        return b;
    if (!b)
        return a;
    if (a->x < b->x)
        std::swap(a, b);
    a->rc = merge(a->rc, b);
    if (!a->lc || a->lc->d < a->rc->d)
        std::swap(a->lc, a->rc);
    a->d = a->rc ? a->rc->d + 1 : 0;
    a->maintain();
    return a;
}
struct Node {
    struct Edge *e;
    int c, l;
    LT *heap;
} g[N];
struct Edge {
    Node *v;
    Edge *next;
    Edge(Node *_u, Node *_v) : v(_v), next(_u->e) {
        _u->e = this;
    }
};
int n, m;
ll ans;
void dfs(Node *u) {
    for (Edge *e = u->e; e; e = e->next)
        dfs(e->v);
    for (Edge *e = u->e; e; e = e->next)
        u->heap = merge(u->heap, e->v->heap);
    while (u->heap->sum > m)
        u->heap = merge(u->heap->lc, u->heap->rc);
    ans = std::max(ans, (ll)u->l * u->heap->siz);
}

int main() {
    static int i, x;
    static Node *rt;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d%d", &x, &g[i].c, &g[i].l);
        if (x)
            new Edge(g + x, g + i);
        else
            rt = g + i;
        g[i].heap = new LT(g[i].c);
    }
    dfs(rt);
    printf("%lld\n", ans);
    return 0;
}
