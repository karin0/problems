#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 44, INF = 0x7f7f7f7f;

int n;
struct Node {
    struct Edge *e, *cur;
    int lvl;
} g[N * N * N], *s, *t;
struct Edge {
    Node *v;
    int cap, flow;
    Edge *next, *rev;
    Edge(Node *_u, Node *_v, int _c) : v(_v), cap(_c), flow(0), next(_u->e) {}
};
void arc(Node *u, Node *v, int cap) {
    u->e = new Edge(u, v, cap);
    v->e = new Edge(v, u, 0);
    u->e->rev = v->e;
    v->e->rev = u->e;
}
bool bfs() {
    static int i;
    static Node *u, *v;
    for (i = 1; i <= n; ++i)
        g[i].lvl = 0, g[i].cur = g[i].e;
    s->lvl = 1;
    std::queue<Node *> q; // **
    q.push(s);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (Edge *e = u->e; e; e = e->next)
            if (e->flow < e->cap && (v = e->v)->lvl == 0) {
                v->lvl = u->lvl + 1;
                if (v == t)
                    return true;
                q.push(v);
            }
    }
    return false;
}
int dfs(Node *u, int lim) {
    if (u == t || lim == 0)
        return lim;
    int res = 0, f;
    for (Edge *&e = u->cur; e; e = e->next) // ***
        if (e->flow < e->cap && e->v->lvl == u->lvl + 1 && (f = dfs(e->v, std::min(lim, e->cap - e->flow))) > 0) {
            e->flow += f;
            e->rev->flow -= f;
            res += f;
            lim -= f;
            if (lim == 0)
                break;
        }
    return res;
}
int dinic() {
    static int res;
    res = 0;
    while (bfs())
        res += dfs(s, INF);
    return res;
}
Node *orz(int x, int y, int z) {
    static Node *mem[N][N][N];
    Node *&p = mem[x][y][z];
    if (p)
        return p;
    return p = g + (++n);
}

int main() {
    static int p, q, r, d, x, y, z, v;
    static Node *u;
    scanf("%d%d%d%d", &p, &q, &r, &d);
    s = orz(0, 0, 0);
    t = orz(0, 0, 1);
    for (z = 1; z <= r; ++z) {
        for (x = 1; x <= p; ++x) {
            for (y = 1; y <= q; ++y) {
                scanf("%d", &v);
                u = orz(x, y, z);
                if (z > 1)
                    arc(orz(x, y, z - 1), u, v);
                else
                    arc(s, u, v);
                if (z == r)
                    arc(u, t, INF);
                if (z > d) {
                    if (x - 1 >= 1)
                        arc(u, orz(x - 1, y, z - d), INF);
                    if (x + 1 <= p)
                        arc(u, orz(x + 1, y, z - d), INF);
                    if (y - 1 >= 1)
                        arc(u, orz(x, y - 1, z - d), INF);
                    if (y + 1 <= q)
                        arc(u, orz(x, y + 1, z - d), INF);
                }// else if (z == d)
                 //   arc(u, s, INF);
            }
        }
    }
    printf("%d\n", dinic());

    return 0;
}
