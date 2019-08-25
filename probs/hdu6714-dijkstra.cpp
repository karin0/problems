#include <akari>

IO<1000000, 1000000> io;

cint N = 1002, M = 2002, mo = 998244353;
cll inf = 0x3f3f3f3f3f3f3f3fll;

struct Node {
    ll d;
    int f;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    int w;
    Edge *e;
    Edge() {}
    Edge(Node *v, int w, Edge *e) : v(v), w(w), e(e) {}
} pool[M << 1], *curr;
inline void arc(Node *u, Node *v, int w) {
    u->e = new (curr++) Edge(v, w, u->e);
    v->e = new (curr++) Edge(u, w, v->e);
}
struct S {
    Node *u;
    ll d;
    S(Node *u, ll d) : u(u), d(d) {}
    bool operator < (const S &rhs) const {
        return d > rhs.d;
    }
};
std::priority_queue<S> q; 

int main() {
    int T;
    io > T;
    while (T--) {
        curr = pool;
        int n, m;
        io > n > m;
        rep (i, 1, n)
            g[i].e = NULL;
        while (m--) {
            int u, v, w;
            io > u > v > w;
            arc(&g[u], &g[v], w);
        }
        int ans = 0;
        rep (s, 1, n) {
            rep (i, 1, n)
                g[i].d = inf;
            Node *u = &g[s];
            u->f = 0;
            q.push(S(u, u->d = 0));
            while (!q.empty()) {
                u = q.top().u;
                q.pop();
                int r = u - g;
                r = r == s ? 0 : std::max(u->f, r);
                for (Edge *e = u->e; e; e = e->e) {
                    Node *v = e->v;
                    ll t = u->d + e->w;
                    if (t < v->d) {
                        v->f = r;
                        q.push(S(v, v->d = t));
                    } else if (t == v->d)
                        v->f = std::min(v->f, r);
                }
            }
            rep (i, 1, n)
                ans += g[i].f;
        }
        (io < (ans >= mo ? ans - mo : ans)) daze;
    }  
}
