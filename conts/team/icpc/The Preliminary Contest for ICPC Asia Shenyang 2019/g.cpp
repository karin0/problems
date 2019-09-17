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

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        char c;
        while (!isdigit(c = getchar()));
        long long n = c - '0';
        int cnt = 0;
        while (isdigit(c = getchar())) {
            n = n * 10 + c - '0';
            ++cnt;
            if (cnt >= 6) {
                cnt = -1;
                while (isdigit(c = getchar()));
                break;
            }
        }
        double a;
        scanf("%lf", &a);
        double x = 5 * a / 3.0;
        double a3 = a * 3, a2 = a * 2;
        for (int i = 2; i <= n; ++i) {
            double ox = x;
            x = a * (a3 + x * 5) / (a2 + x * 3);
            if (fabs(x - ox) <= 1e-7)
                break;
            ccc(i, x);
        }
       /* if (cnt < 0)
            ans = 0;
        else
            ans = 5 * a / (3 * n);
            */
        printf("%.10f\n", x);
    }
}
