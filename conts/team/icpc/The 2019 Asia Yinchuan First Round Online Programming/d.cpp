#pragma GCC optimize("Ofast", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
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

cint N = 52;
double f[N][N];
inline double sol1(int n) {
    if (n == 1)
        return 1;
    memset(f, 0, sizeof(f));
    double t = 1.0 / n;
    f[1][0] = t;
    rep (j, 2, n)
        f[1][j] = t;
    rep (i, 2, n) {
        double r = f[i - 1][i] / (n - i + 1);
        f[i][0] = f[i - 1][0] + r;
        re (j, i + 1, n)
            f[i][j] = f[i - 1][j] + r;
    }
    return f[n - 1][0];
}
inline double sol2(int n) {
    double ans = 1;
    re (k, 1, n) {
        memset(f, 0, sizeof(f));
        double t = 1.0 / (n - k + 1);
        f[k][0] = t;
        ccc(k, k, 0, f[k][0]);
        rep (j, k + 1, n) {
            f[k][j] = t;
            ccc(k, k, j, f[k][j]);
        }
        re (i, k + 1, n) {
            double r = f[i - 1][i] / (n - i + 1);
            f[i][0] = f[i - 1][0] + r;
            ccc(k, i, 0, f[i][0]);
            rep (j, i + 1, n) {
                f[i][j] = f[i - 1][j] + r;
                ccc(k, i, j, f[i][j]);
            }
        }
        ccc(k, f[n - 1][0]);
        ans += f[n - 1][0];
    }
    return ans / n;
}

int main() {
    /*rep (i, 1, 3) {
        ccc(i, sol1(i), sol2(i));
    }*/
    int T;
    scanf("%d", &T);
    rep (ks, 1, T) {
        int n, m;
        scanf("%d%d", &n, &m);
        printf("Case #%d: %.6f %.6f\n", ks, sol1(n), sol2(m));
    }
}
