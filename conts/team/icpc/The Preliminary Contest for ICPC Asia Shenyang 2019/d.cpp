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

const int N = 100003, mo = 1000000007;
struct Node {
    int f[3], h[3];
    struct Edge *e;
    void clear() {
        e = NULL;
        // h[0] = h[1] = h[2] = f[0] = f[1] = f[2] =0;
    }
} g[N];

struct Edge {
    Node *v;
    int w;
    Edge *e;
    Edge() {}
    Edge(Node *v, int w, Edge *e) : v(v), w(w), e(e) {}
} pool[N << 1], *curr;

inline void arc(Node *u, Node *v, int w) {
    u->e = new (curr++) Edge(v, w, u->e);
    v->e = new (curr++) Edge(u, w, v->e);
}

void dfs1(Node *u, Node *fa) {
    Node *v;
    u->f[0] = 1;
    u->f[1] = u->f[2] = 0;
    for (Edge *e = u->e; e; e = e->e) if ((v = e->v) != fa) {
        dfs1(v, u);
#define F(i, j, k) u->f[0] += v->f[i], u->f[1] += v->f[j], u->f[2] += v->f[k]; break;
        switch (e->w % 3) {
            case 0: F(0, 1, 2);
            case 1: F(2, 0, 1);
            default: F(1, 2, 0);
        }
    }
}
void dfs2(Node *u, Node *fa) {
    Node *v;
    for (Edge *e = u->e; e; e = e->e) if ((v = e->v) != fa) {
#define H(i, j, k) v->h[i] = u->h[j] + u->f[j] - v->f[k]
        switch (e->w % 3) {
            case 0: H(0, 0, 0); H(1, 1, 1); H(2, 2, 2); break;
            case 1: H(0, 2, 1); H(1, 0, 2); H(2, 1, 0); break;
            default: H(0, 1, 2); H(1, 2, 0); H(2, 0, 1);
        }
        ccc(u-g, v-g, v->h[0], v->h[1], v->h[2]);
        dfs2(v, u);
    }
}


int ans[3];

void dfs3(Node *u, Node *fa) {
    Node *v;
    //re (i, 0, 3)
    //    ccc(u-g, i, u->f[i], u->h[i]);
    for (Edge *e = u->e; e; e = e->e) if ((v = e->v) != fa) {
        dfs3(v, u);
#define G(i, j) (ll)v->f[i] * v->h[j]
#define R(i, j, k) ((G(0, i) + G(1, j) + G(2, k)) % mo * (ll)e->w) % mo
        ans[0] = (ans[0] + R(0, 2, 1)) % mo;
        ans[1] = (ans[1] + R(1, 0, 2)) % mo;
        ans[2] = (ans[2] + R(2, 1, 0)) % mo;
    }
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        curr = pool;
        re (i, 1, n) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            arc(&g[u], &g[v], w);
        }
        dfs1(&g[0], NULL);
        dfs2(&g[0], NULL);
        dfs3(&g[0], NULL);
        printf("%d %d %d\n", (ans[0] << 1) % mo, (ans[1] << 1) % mo, (ans[2] << 1) % mo);
        re (i, 0, n)
            g[i].clear();
        ans[0] = ans[1] = ans[2] = 0;
    }
}
