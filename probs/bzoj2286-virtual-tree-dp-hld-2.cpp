#include <cstdio>
#include <climits>
#include <algorithm>
 
typedef long long ll;
const int N = 250003;
struct Node {
    struct Edge *e;
    struct VEdge *ve;
    ll w;
    Node *fa, *top, *hch;
    bool key;
    int dfn, siz, dep;
} g[N];
struct Edge {
    Node *v;
    Edge *next;
    ll w;
    Edge(Node *_u, Node *_v, ll _w) : v(_v), next(_u->e), w(_w) {
        _u->e = this;
    }
};
struct VEdge {
    Node *v;
    VEdge *next;
};
struct HLD {
    void dfs1(Node *u) {
        u->siz = 1;
        for (Edge *e = u->e; e; e = e->next) {
            Node *v = e->v;
            if (!v->siz) {
                v->fa = u;
                v->dep = u->dep + 1;
                v->w = std::min(u->w, e->w);
                dfs1(v);
                u->siz += v->siz;
                if (!u->hch || v->siz > u->hch->siz)
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
        for (Edge *e = u->e; e; e = e->next) {
            Node *v = e->v;
            if (v != u->hch && v->fa == u) // ***
                dfs2(v, v);
        }
    }
    void init() {
        g[1].dep = 1;
        g[1].w = LLONG_MAX;
        dfs1(&g[1]);
        dfs2(&g[1], &g[1]);
    }
    Node *lca(Node *u, Node *v) {
        while (u->top != v->top) {
            if (u->top->dep < v->top->dep)
                std::swap(u, v);
            u = u->top->fa;
        }
        if (u->dep < v->dep)
            std::swap(u, v);
        return v;
    }
} hld;
bool cmp(const Node *u, const Node *v) {
    return u->dfn < v->dfn;
}
struct VirtualTree {
    VEdge pool[N << 1];
    int vecnt;
    void varc(Node *u, Node *v) {
        VEdge &e = pool[++vecnt];
        e.v = v, e.next = u->ve, u->ve = &e;
        u->key = v->key = false;
    }
    void build(Node *a[], int n) {
        static Node *sta[N];
        static int top, i;
        vecnt = 0;
        std::sort(a + 1, a + n + 1, cmp);
        top = 0, sta[++top] = &g[1];
        for (i = 1; i <= n; ++i) {
            Node *u = a[i];
            Node *l = hld.lca(u, sta[top]);
            while (top > 1 && sta[top - 1]->dep > l->dep)
                varc(sta[top - 1], sta[top]), --top;
            if (sta[top] != l) varc(l, sta[top]);
            --top;
            if (sta[top] != l) sta[++top] = l;
            sta[++top] = u;
        }
        while (top > 1)
            varc(sta[top - 1], sta[top]), --top;
        for (i = 1; i <= n; ++i)
            a[i]->key = true;
    }
    ll dp(Node *u) {
        // printf("To %ld\n", u - g);
        // printf("Just %d\n", u->w);
        if (u->key || !u->ve)
            return u->w;
        ll s = 0;
        for (VEdge *e = u->ve; e; e = e->next)
            s += dp(e->v);
        // printf("%ld's Sum is %lld\n", u - g, s);
        u->ve = NULL; // **
        return std::min(s, (ll)u->w);
    }
} vtree;
int main() {
    static int n, m, k, i, u, v;
    static ll w;
    static Node *a[N];
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        scanf("%d%d%lld", &u, &v, &w);
        new Edge(g + u, g + v, w);
        new Edge(g + v, g + u, w);
    }
    hld.init();
    scanf("%d", &m);
    while (m--) {
        scanf("%d", &k);
        for (i = 1; i <= k; ++i)
            scanf("%d", &u), a[i] = &g[u];
        vtree.build(a, k);
        printf("%lld\n", vtree.dp(&g[1]));
    }
 
    return 0;
}

