#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;

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
    #define crep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

const int N = 50003;
int n, X, Y;
struct Node {
    int w, sum, s2;
    bool flp, used;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *v, Edge *e) : v(v), e(e) {}
} pool[N], *curr = pool;

void dfs1(Node *u, bool flip) {
    flip ^= u->flp;
    if (flip)
        u->w = -u->w;
    u->sum = u->w;
    // int cost = u->flp ? Y : X, smin = 0, smax = 0;
    for (Edge *e = u->e; e; e = e->e) {
        Node *v = e->v;
        dfs1(v, flip);
        // smin += v->fmin;
        // smax += v->fmax;
        u->sum += v->sum;
    }
    // u->fmax = std::max(smax + u->w, -smin - u->w - cost);
    // u->fmin = std::min(smin + u->w, -smax - u->w - cost);
    // ccc(u-g, u->fmax, u->fmin);
}
/*
void dfs2(Node *u, bool flip) {
    int cost = u->flp ? Y : X;
    if (flip) {
        u->sum = -u->sum;
        u->w = -u->w;
    }
    if (-2 * u->sum > cost) {
        flip ^= 1;
        u->s2 = -u->w - cost;
    } else
        u->s2 = u->w;
    for (Edge *e = u->e; e; e = e->e) {
        Node *v = e->v;
        dfs2(v, flip);
        u->s2 += v->s2;
    }
}*/
void dfs2(Node *u, bool flip) {
    int cost = u->flp ? Y : X;
    if (flip) {
        u->sum = -u->sum;
        u->w = -u->w;
    }
    if (u != g && -2 * u->sum > cost) {
        flip ^= 1;
        u->w = -u->w - cost;
    }
    u->s2 = u->w;
    for (Edge *e = u->e; e; e = e->e) {
        Node *v = e->v;
        dfs2(v, flip);
        u->s2 += v->s2;
    }
}

int main() {
    while (scanf("%d%d%d", &n, &X, &Y) == 3) {
        curr = pool;
        rep (i, 0, n) {
            g[i].e = NULL;
            g[i].used = false;
        }
        rep (i, 1, n) {
            int v, f, s, p;
            scanf("%d%d%d%d", &v, &f, &s, &p);
            g[i].w = p ? -v : v;
            g[i].flp = s;
            g[f].e = new (curr++) Edge(&g[i], g[f].e);
        }
        g[0].w = 0;
        dfs1(&g[0], false);
        dfs2(&g[0], false);
        if (g[0].s2 < 0)
            puts("HAHAHAOMG");
        else
            printf("%d\n", g[0].s2);
    }
}