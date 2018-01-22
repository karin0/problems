#include <cstdio>
#include <algorithm>
#include <queue>

typedef long long ll;
const int N = 100005, mo = 1000000007;
int n;
ll inv[N];
void inv_calc() {
    static int i;
    inv[1] = 1;
    for (i = 2; i <= n; ++i)
        inv[i] = (mo - mo / i) * inv[mo % i] % mo; // ***
}
struct Node {
    struct Edge *e;
    int ind, ind2;
    ll f;
} g[N];
struct Edge {
    Node *v;
    Edge *next;
    Edge(Node *_u, Node *_v) : v(_v), next(_u->e) {
        _u->e = this;
    }
};
void topo_sort() {
    static std::queue<Node *> q;
    static Node *u;
    q.push(g + 1);
    while (!q.empty()) {
        u = q.front();
        q.pop(); // ***
        u->f = u->f * inv[u->ind] % mo;
        for (Edge *e = u->e; e; e = e->next)
            if (e->v->ind2) {
                e->v->f = (e->v->f + u->f) % mo;
                if (--e->v->ind2 == 0)
                    q.push(e->v);
            }
    }
}
int main() {
    static int m, x, y, i, u, v;
    static ll orz = 1;
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        new Edge(g + u, g + v);
        ++g[v].ind;
    }
    for (i = 1; i <= n; ++i)
        g[i].ind2 = g[i].ind;
    ++g[y].ind;
    for (i = 2; i <= n; ++i)
        orz = orz * g[i].ind % mo;
    if (y == 1) {
        printf("%lld\n", orz);
        return 0;
    }
    inv_calc();
    g[y].f = orz;
    topo_sort();
    printf("%lld\n", (orz - g[x].f + mo) % mo);

    return 0;
}
