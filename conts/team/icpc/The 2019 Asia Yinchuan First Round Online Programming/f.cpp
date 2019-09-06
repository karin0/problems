#pragma GCC optimize("Ofast", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
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


int d[203][203][203];
std::pair<int, int> a[203];
int main() {
    int T;
    scanf("%d", &T);
    rep (ks, 1, T) {
        printf("Case #%d:\n", ks);
        int n, q;
        scanf("%d%d", &n, &q);
        rep (i, 1, n) {
            scanf("%d", &a[i].first);
            a[i].second = i;
        }
        std::sort(a + 1, a + n + 1);
        auto dt = d[0];
        rep (i, 1, n) rep (j, 1, n)
            scanf("%d", &dt[i][j]);
        rep (t, 1, n) {
            int k = a[t].second;
            dt = d[t];
            auto dtt = d[t - 1];
            rep (i, 1, n) {
                int *dti = dt[i];
                int *dtti = dtt[i];
                re (j, 1, i)
                    dti[j] = std::min(dtti[j], (i > k ? dtti[k] : dtt[k][i]) + (j > k ? dtt[j][k] : dtt[k][j]));
            }
        }
        while (q--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            int t = std::upper_bound(a + 1, a + n + 1, std::make_pair(w, 30000)) - a - 1;
            printf("%d\n", u > v ? d[t][u][v] : d[t][v][u]);
        }
    }
}
