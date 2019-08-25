#include <cstdio>
#include <algorithm>
#include <iostream>
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


int to[10], nxt[10], g[10], ec;
inline void arc(int u, int v) {
    to[++ec] = v;
    nxt[ec] = g[u];
    g[u] = ec;
}
int mxd = 0;
void dfs(int u, int fa = 0, int dep = 0) {
    mxd = std::max(mxd, dep);
    for (int e = g[u]; e; e = nxt[e]) if (to[e] != fa)
        dfs(to[e], u, dep + 1);
}

int deg[10], cnt[10];
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        rep (i, 1, 6)
            deg[i] = cnt[i] = g[i] = 0;
        ec = mxd = 0;
        int s;
        rep (i, 1, 5) {
            int u, v;
            scanf("%d%d", &u, &v);
            deg[u]++;
            deg[v]++;
            arc(u, v);
            arc(v, u);
        }
        rep (i, 1, 6) {
            cnt[deg[i]]++;
            if (deg[i] == 3)
                s = i;
        }
        if (cnt[4])
            puts("2,2-dimethylbutane");
        else if (cnt[2] == 4)
            puts("n-hexane");
        else if (cnt[3] >= 2)
            puts("2,3-dimethylbutane");
        else if (dfs(s), mxd >= 3)
            puts("2-methylpentane");
        else
            puts("3-methylpentane");
    }
}