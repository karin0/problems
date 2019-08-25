

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
    #define FI "joy"
#endif

const int N = 10005;
struct S {
    int t, x, y;
} a[N];
int wx[N], wy[N];
int main() {
#ifdef FI
    freopen(FI ".in", "r", stdin);
    freopen(FI ".out", "w", stdout);
#endif
    int sx, sy, fx, fy;
    int n, k, vmax;
    scanf("%d%d%d%d%d%d%d", &sx, &sy, &fx, &fy, &n, &k, &vmax);
    rep (i, 1, n) {
        S &x = a[i];
        scanf("%d%d%d", &x.t, &x.x, &x.y);
    }
    a[n + 1].t = k;
    int ddx = sx, ddy = sy;
    rep (i, 1, n) {
        S &x = a[i];
        int uu = a[i + 1].t - 1;
        rep (j, a[i].t, uu) {
            wx[j] = x.x;
            wy[j] = x.y;
            ddx += x.x;
            ddy += x.y;
        }
    }
    int ux = fx - ddx, uy = fy - ddy;
    ll vk = (ll)vmax * k;
    if ((ll)ux * ux + (ll)uy * uy > vk * vk) {
        puts("No");
        return 0;
    }
    puts("Yes");
    double dx = (double)ux / k, dy = (double)uy / k, px = sx, py = sy;
    re (i, 0, k) {
        px += dx + wx[i];
        py += dy + wy[i];
        printf("%.10f %.10f\n", px, py);
    }
}