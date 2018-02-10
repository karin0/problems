#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>

const int N = 66, M = 66;
namespace G {
    int n;
    struct Node {
        struct Edge *e, *prev;
        int flow, dis;
        bool inq;
    } g[N * M], *s, *t;
    struct Edge {
        Node *u, *v;
        Edge *e, *rev;
        int cap, flow, w;
        /*
        Edge(Node *_u, Node *_v, int _c, int _w, Edge *_r = NULL) : u(_u), v(_v), e(_u->e), rev(_r ? _r : new Edge(_v, _u, 0, -_w, this)), cap(_c), flow(0), w(_w) {
            _u->e = this;
        }*/
        //Edge(Node *_u, Node *_v, int _c, int _w) : u(_u), v(_v), e(_u->e), cap(_c), flow(0), w(_w) {}
    } pool[N * N * N * 2];
    int ecnt;
    inline Edge *new_edge(Node *u, Node *v, int c, int w) {
        ++ecnt;
        pool[ecnt].u = u;
        pool[ecnt].v = v;
        pool[ecnt].cap = c;
        pool[ecnt].w = w;
        pool[ecnt].e = u->e;
        return pool + ecnt;
    }
    inline void arc(Node *u, Node *v, int c, int w) {
        u->e = new_edge(u, v, c, w);
        v->e = new_edge(v, u, 0, -w);
        u->e->rev = v->e;
        v->e->rev = u->e;
    }
    int mcmf() {
        static std::queue<Node *> q;
        static int flow, cost;
        static Node *u, *v;
        while (true) {
            for (u = g + 1; u <= g + n; ++u) {
                u->prev = NULL;
                u->flow = 0;
                u->dis = INT_MAX;
                u->inq = false;
            }
            s->flow = INT_MAX;
            s->dis = 0;
            s->inq = true;
            q.push(s);
            while (!q.empty()) {
                u = q.front();
                q.pop();
                u->inq = false;
                for (Edge *e = u->e; e; e = e->e)
                    if (e->flow < e->cap && (v = e->v)->dis > u->dis + e->w) {
                        v->dis = u->dis + e->w;
                        v->prev = e;
                        v->flow = std::min(u->flow, e->cap - e->flow);
                        if (!v->inq) {
                            v->inq = true;
                            q.push(v);
                        }
                    }
            }
            if (t->dis == INT_MAX)
                break;
            for (Edge *e = t->prev; e; e = e->u->prev) {
                e->flow += t->flow;
                e->rev->flow -= t->flow;
            }
            flow += t->flow;
            cost += t->dis * t->flow;
        }
        return cost;
    }
}
using G::Node;
using G::arc;
using G::s;
using G::t;
int n, m;
inline Node *f(int i, int j) {
    /*
    static Node *mem[N][M];
    return mem[i][j] ? mem[i][j] : (mem[i][j] = G::g + (++G::n));
    */
    return G::g + (j * (n + 1) + i + 1);
}

int main() {
    static int a[N][M], i, j, k;
    scanf("%d%d", &m, &n);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            scanf("%d", &a[i][j]);
    s = f(0, 0), t = f(0, 1);
    G::n = f(n, m) - G::g;
    for (i = 1; i <= n; ++i)
        arc(s, f(i, 0), 1, 0);
    for (k = 1; k <= n; ++k)
        for (i = 1; i <= n; ++i)
            for (j = 1; j <= m; ++j)
                arc(f(k, 0), f(i, j), 1, a[k][j] * i);
    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            arc(f(i, j), t, 1, 0);
    printf("%.2lf\n", (double)G::mcmf() / n);

    return 0;
}
