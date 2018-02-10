#include <cstdio>
#include <algorithm>

const int N = 40004;
struct Node {
    struct Edge *e;
    int siz, ms, dep;
    bool done;
} g[N];
struct Edge {
    Node *v;
    int w;
    Edge *next;
    Edge(Node *_u, Node *_v, int _w) : v(_v), w(_w), next(_u->e) {
        _u->e = this;
    }
};
int n, k;

Node *a[N];
int d[N], cnt;
void dfs1(Node *u, Node *f) {
    a[++cnt] = u;
    u->siz = 1, u->ms = 0;
    for (Edge *e = u->e; e; e = e->next)
        if (e->v != f && !e->v->done) {
            dfs1(e->v, u);
            u->siz += e->v->siz;
            u->ms = std::max(u->ms, e->v->siz);
        }
}
Node *center(Node *u) {
    cnt = 0;
    dfs1(u, NULL);
    Node *res = u;
    for (int i = 1; i <= cnt; ++i) {
        a[i]->ms = std::max(a[i]->ms, u->siz - a[i]->ms);
        if (res->ms > a[i]->ms)
            res = a[i];
    }
    return res;
}
void dfs2(Node *u, Node *f) {
    d[++cnt] = u->dep;
    for (Edge *e = u->e; e; e = e->next)
        if (e->v != f && !e->v->done) {
            e->v->dep = u->dep + e->w; // ***
            dfs2(e->v, u);
        }
}
int calc(Node *u, int w) {
    cnt = 0;
    u->dep = w;
    dfs2(u, NULL);
    std::sort(d + 1, d + cnt + 1);
    int res = 0;
    for (int i = 1, j = cnt; i < j; ++i) {
        while (i < j && d[i] + d[j] > k)
            --j;
        res += j - i;
    }
    return res;
}

int ans;
void build(Node *u) {
    u = center(u);
    u->done = true;
    ans += calc(u, 0);
    for (Edge *e = u->e; e; e = e->next)
        if (!e->v->done)
            ans -= calc(e->v, e->w), solve(e->v);
}

int main() {
    static int m, i, u, v, w;
    scanf("%d%d", &n, &m);
    for (i = 1; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        new Edge(g + u, g + v, w);
        new Edge(g + v, g + u, w);
    }
    build();
    while (m--) {
        scanf("%d%d", &u, &w);
        update(&g[u], w);
    }
    solve(g + 1);
    return 0;
}
