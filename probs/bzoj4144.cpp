#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>

typedef long long ll;
const int N = 200003, _2e9 = 2000000000;
const ll INF = 1ll << 50;
struct Node {
    struct Edge *e;
    Node *gas;
    ll d;
    bool inq;
} g[N];
struct Edge {
    Node *v;
    int w;
    Edge *next;
    Edge(Node *_u, Node *_v, int _w) : v(_v), w(_w), next(_u->e) {
        _u->e = this;
    }
};
struct Triple {
    int u, v, w;
} es[N];
std::queue<Node *> q;
void spfa() { // 卡 dij
    while (!q.empty()) {
        Node *u = q.front();
        q.pop();
        u->inq = false;
        for (Edge *e = u->e; e; e = e->next) {
            Node *v = e->v;
            if (v->d > u->d + e->w) {
                v->d = u->d + e->w;
                v->gas = u->gas;
                if (!v->inq) {
                    v->inq = true;
                    q.push(v);
                }
            }
        }
    }
}
struct DisjointSet {
    int fa[N];
    void init(int _n) {
        for (int i = 1; i <= _n; ++i)
            fa[i] = i;
    }
    int find(int x) {
        return (fa[x] == x) ? x : (fa[x] = find(fa[x]));
    }
    void unite(int x, int y) {
        fa[find(x)] = find(y);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
} ds;
struct Opt {
    int u, v, w, ind;
    Opt() {}
    Opt(int _u, int _v, int _w, int _i) : u(_u), v(_v), w(_w), ind(_i) {}
    bool operator < (const Opt &b) const {
        return w < b.w || (w == b.w && ind < b.ind);
    }
} qwq[N + N];
int main() {
    static int n, s, m, t, i, u, v, w, qcnt;
    static bool ans[N];
    scanf("%d%d%d", &n, &s, &m);
    for (i = 1; i <= n; ++i)
        g[i].d = INF;
    for (i = 1; i <= s; ++i) {
        scanf("%d", &u);
        g[u].d = 0;
        g[u].gas = &g[u];
        g[u].inq = true;
        q.push(&g[u]);
    }
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        es[i] = (Triple){u, v, w};
        new Edge(&g[u], &g[v], w);
        new Edge(&g[v], &g[u], w);
    }
    spfa();
    for (i = 1; i <= m; ++i) {
        u = es[i].u, v = es[i].v, w = es[i].w;
        if ((ll)w + g[u].d + g[v].d > _2e9)
            continue;
        if (g[u].gas == g[v].gas)
            continue;
        qwq[++qcnt] = Opt(g[u].gas - g, g[v].gas - g, w + g[u].d + g[v].d, -1);
    }
    scanf("%d", &t);
    for (i = 1; i <= t; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        qwq[++qcnt] = Opt(u, v, w, i);
    }
    std::sort(qwq + 1, qwq + qcnt + 1);
    ds.init(n);
    for (i = 1; i <= qcnt; ++i) {
        Opt &qaq = qwq[i];
        if (qaq.ind == -1)
            ds.unite(qaq.u, qaq.v);
        else
            ans[qaq.ind] = ds.same(qaq.u, qaq.v);
    }
    for (i = 1; i <= t; ++i)
        puts(ans[i] ? "TAK" : "NIE");

    return 0;
}
