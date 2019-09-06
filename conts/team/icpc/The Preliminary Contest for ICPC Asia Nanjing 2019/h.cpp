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

cint inf = 0x3f3f3f3f;
int d[305][305];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        re (i, 0, n) {
            re (j, 0, n)
                d[i][j] = inf;
            d[i][i] = 0;
        }
        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            d[u][v] = w;
        }
        rep (t, 1, 6) {
            re (k, 0, n) re (i, 0, n) re (j, 0, n)
                d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n", d[u][v] = -d[v][u]);
        }
    }
}
