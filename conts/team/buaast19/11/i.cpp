#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;
typedef unsigned long long ull;

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


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int x, y, nx, ny;
        scanf("%d%d", &x, &y);
        double l = std::min(x, y);//  sqrt((ll)x * x + (ll)y * y);
        int x0 = round(x / l);
        int y0 = round(y / l);
        if (!x0) ++x0;
        if (!y0) ++y0;
        ccc(x0, y0);
        if (x % x0 == 0 && y % y0 == 0 && (x / x0) == (y / y0))
            ++x0;
        if ((ll)y0 * x < (ll)y * x0) { // 下方
            nx = x;
            ny = ((ll)x * y0 - 1) / x0;
        } else {
            nx = ((ll)y * x0 - 1) / y0;
            ny = y;
        }
        // (x0, y0), (x, y), (nx, ny)
        ccc(l, (fabs((double)x0 * y - (double)y0 * x) + fabs((double)x0 * ny - (double)y0 * nx)) / 2.0);
        printf("4\n0 0\n%d %d\n%d %d\n%d %d\n", nx, ny, x0, y0, x, y);
    }
}