#include <cstdio>
#include <algorithm>

typedef unsigned long long ull;
const int N = 1003;
struct Node {
    int x, y, z;
    bool vis;
    struct Edge *e;
} g[N], *s, *t;
struct Edge {
    Node *v;
    Edge *e;
} pool[N * N], *curr;
void arc(Node *u, Node *v) {
    *curr = (Edge){v, u->e};
    u->e = curr++;
}
ull sqr;
bool connected(const Node &u, const Node &v) {
    static ull dx, dy, dz;
    dx = std::abs(u.x - v.x), dy = std::abs(u.y - v.y), dz = std::abs(u.z - v.z);
    dx *= dx, dy *= dy, dz *= dz;
    return sqr >= dz && dx + dy <= sqr - dz;
}
void dfs(Node *u) {
    u->vis = true;
    for (Edge *e = u->e; e; e = e->e)
        if (!e->v->vis) {
            dfs(e->v);
            if (t->vis)
                return;
        }
}
int main() {
    static int ks, i, j, n, h, r;
    scanf("%d", &ks);
    while (ks--) {
        curr = pool;
        scanf("%d%d%d", &n, &h, &r);
        sqr = (ull)4 * r * r;
        s = &g[n], t = &g[n + 1];
        s->vis = t->vis = false, s->e = t->e = NULL;
        for (i = 0; i < n; ++i) {
            scanf("%d%d%d", &g[i].x, &g[i].y, &g[i].z);
            g[i].vis = false, g[i].e = NULL;
            for (j = 0; j < i; ++j)
                if (connected(g[i], g[j]))
                    arc(&g[i], &g[j]), arc(&g[j], &g[i]);
            if (std::abs(g[i].z) <= r)
                arc(s, &g[i]);
            if (std::abs(h - g[i].z) <= r)
                arc(&g[i], t);
        }
        dfs(s);
        puts(t->vis ? "Yes" : "No");
    }
    return 0;
}
