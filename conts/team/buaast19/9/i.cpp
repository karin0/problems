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

int c[1999];
int main() {
    int n;
    scanf("%d", &n);
    rep (i, 1, n) {
        int l, r;
        scanf("%d%d", &l, &r);
        ++c[l];
        --c[r + 1];
    }
    int m = 1826;
    rep (i, 2, m)
        c[i] += c[i - 1];
    rep (i, 2, m)
        c[i] += c[i - 1];
    for (int i = 1, t; (t = i + 180 - 1) <= m; ++i) {
        if (c[t] - c[i - 1] > 90)
            return puts("No"), 0;
        // ccc(i, t, c[t] - c[i-1]);
    }
    puts("Yes");
}