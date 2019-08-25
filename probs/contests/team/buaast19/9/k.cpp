#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
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

const int N = 200003, M = 400003;
std::vector<int> g[N];
int cnt, n;
bool done[N];
void dfs(int u) {
    if (done[u])
        return;
    done[u] = true;
    for (int p : g[u])
        dfs(p);
    printf("%d%c", u, ++cnt == n ? '\n' : ' ');
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    rep (i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[v].push_back(u);
    }
    rep (i, 1, n)
        std::sort(g[i].begin(), g[i].end());
    rep (i, 1, n) {
        dfs(i);
        if (cnt >= n)
            return 0;
    }
}