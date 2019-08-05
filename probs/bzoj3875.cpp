#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 200005;
typedef long long ll;
int n;
struct Node {
    struct Edge *e, *er; // rev
    ll s, k, f;
    bool inq;
} g[N];
struct Edge {
    Node *v;
    Edge *next;
    Edge(Node *_u, Node *_v, bool _r = false) : v(_v) {
        if (_r)
            next = _u->er, _u->er = this;
        else
            next = _u->e, _u->e = this;
    }
};
struct Item {
    Node *u;
    ll f;
    bool operator < (const Item &b) const {
        return f > b.f;
    }
};
std::priority_queue<Item> que;
void bfs() {
    static Node *u;
    static ll c;
    while (!que.empty()) {
        u = que.top().u;
        que.pop();
        u->inq = false;
        c = u->s;
        for (Edge *e = u->e; e; e = e->next)
            c += e->v->f;
        if (c < u->f)
            u->f = c;
            for (Edge *e = u->er; e; e = e->next)
                if (!e->v->inq)
                    que.push((Item){e->v, e->v->f});
        }
    }
}
int main() {
    static int i, j, x, r;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%lld%lld%d", &g[i].s, &g[i].k, &r);
        g[i].f = g[i].k;
        que.push((Item){g + i, g[i].f});
        g[i].inq = true;
        for (j = 1; j <= r; ++j) {
            scanf("%d", &x);
            new Edge(g + i, g + x), new Edge(g + x, g + i, true);
        }
    }
    bfs();
    printf("%lld\n", g[1].f);

    return 0;
}
