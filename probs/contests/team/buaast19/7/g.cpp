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

#ifndef AKARI
    #define FI "grave"
#endif

int ww[10], hh[10];



int main() {
#ifdef FI
    freopen(FI ".in", "r", stdin);
    freopen(FI ".out", "w", stdout);
#endif
    int x1, y1, x2, y2, x3, y3, x4, y4, w, h;
    scanf("%d%d%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4, &w, &h);
    ww[0] = x2 - x1, hh[0] = y2 - y4;
    ww[1] = ww[0], hh[1] = y3 - y1;
    ww[2] = x3 - x1, hh[2] = y2 - y1;
    ww[3] = x2 - x4, hh[3] = hh[2];
    rep (i, 0, 3) if (w <= ww[i] && h <= hh[i]) {
        puts("Yes");
        return 0;
    }
    puts("No");

}