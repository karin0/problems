#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;

using std::abs;
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

const int N = 100003;
struct Edge {
    int v;
    Edge *e;
    Edge() {}
    Edge(int v, Edge *e) : v(v), e(e) {}
} pool[N << 1], *curr, *g[N];
int l[N], r[N];
ll fl[N], fr[N];

void dfs(int u, int fa) {
    fl[u] = fr[u] = 0;
    for (Edge *e = g[u]; e; e = e->e) if (e->v != fa) {
        dfs(e->v, u);
        fl[u] += std::max(abs(l[u] - l[e->v]) + fl[e->v],
                          abs(l[u] - r[e->v]) + fr[e->v]);
        fr[u] += std::max(abs(r[u] - l[e->v]) + fl[e->v],
                          abs(r[u] - r[e->v]) + fr[e->v]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        curr = pool;
        int n;
        scanf("%d", &n);
        re (i, 1, n) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u] = new (curr++) Edge(v, g[u]);
            g[v] = new (curr++) Edge(u, g[v]);
        }
        rep (i, 1, n)
            scanf("%d%d", &l[i], &r[i]);
        dfs(1, 0);
        printf("%lld\n", std::max(fl[1], fr[1]));
        if (T) rep (i, 1, n)
            g[i] = NULL;
    }
}
