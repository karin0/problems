#include <akari>

IO<1000000, 1000000> io;

cint N = 100002;

struct Edge {
    int v, w;
    Edge *e;
    Edge() {}
    Edge(cint v, cint w, Edge *const e) : v(v), w(w), e(e) {}
} pool[N << 1], *curr = pool, *g[N];

struct S {
    int u;
    ll d;
    S(int u, ll d) : u(u), d(d) {}
    bool operator < (const S &rhs) const {
        return d > rhs.d;
    }
};
std::priority_queue<S> q;
ll d[N];
int pre[N], sta[N];

int main() {
    int n, m;
    io > n > m;
    while (m--) {
        int u, v, w;
        io > u > v > w;
        if (u == v)
            continue;
        g[u] = new (curr++) Edge(v, w, g[u]);
        g[v] = new (curr++) Edge(u, w, g[v]);
    }
    cll inf = 0x3f3f3f3f3f3f3f3fll;
    memset(d + 2, 0x3f, sizeof(*d) * (n - 1));
    q.push(S(1, 0));
    while (!q.empty()) {
        int u = q.top().u;
        q.pop();
        for (Edge *e = g[u]; e; e = e->e) {
            ll t = d[u] + e->w;
            if (d[e->v] > t) {
                q.push(S(e->v, d[e->v] = t));
                pre[e->v] = u;
            }
        }
    }

    if (d[n] >= inf) {
        io << '-' << '1' << '\n';
        return 0;
    }
    int *p = sta;
    for (int u = n; u; u = pre[u])
        *p++ = u;
    while (--p != sta)
        (io - *p) << ' ';
    (io - n) << '\n';

    return 0;
}
