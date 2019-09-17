#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;

#ifdef AKARI
void cca() {
    std::cerr << "\033[39;0m" << std::endl;
}
template <typename T, typename... Args>
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", cca(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) rep(i, s_, t_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

const int mo = 1000000007, N = 1000003;

int inv[N];
struct Node {
    int dep, f;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *v, Edge *e) : v(v), e(e) {}
} pool[N << 1], *curr = pool;
inline void arc(Node *u, Node *v) {
    u->e = new (curr++) Edge(v, u->e);
    v->e = new (curr++) Edge(u, v->e);
}
int depth;
void dfs1(Node *u, int d) {
    depth = std::max(depth, u->dep = d);
    for (Edge *e = u->e; e; e = e->e) if (!e->v->dep)
        dfs1(e->v, d + 1);
};
int qpow(ll a, int n) {
    ll res = 1;
    for (; n; n >>= 1, a = a * a % mo)
        if (n & 1)
            res = res * a % mo;
    return res;
}
void dfs2(Node *u, Node *fa) {
    if (u->f == -1) {
        u->f = 0;
        return;
    }
    int k = 0, sf = 0;
    for (Edge *e = u->e; e; e = e->e) if (e->v != fa) {
        // u->ok |= e->v->ok;
        dfs2(e->v, u);
        sf += e->v->f;
        if (sf >= mo)
            sf -= mo;
        ++k;
    }
    if (k)
        u->f = sf ? qpow((ll)sf * inv[k] % mo, k) : 0;
    else
        u->f = 1;
    ccc(u-g, sf, k, inv[k]);
    ccc(u-g, u->f);
};

int main() {
    int n;
    scanf("%d", &n);
    inv[1] = 1;
    rep (i, 2, n)
        inv[i] = (ll)(mo - mo / i) * inv[mo % i] % mo;
    re (i, 1, n) {
        int u, v;
        scanf("%d%d", &u, &v);
        arc(&g[u], &g[v]);
    }
    dfs1(&g[1], 1);
    rep (i, 1, n) if (g[i].dep == depth) {
        g[i].f = -1;
    }
    dfs2(&g[1], NULL);
    int t = 1 - g[1].f;
    if (t < 0)
        t += mo;
    printf("%d\n", t);
}
