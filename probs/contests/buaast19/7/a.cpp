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
    #define FI "alarm"
#endif

int w[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int hh[50], mm[50];

int main() {
#ifdef FI
    freopen(FI ".in", "r", stdin);
    freopen(FI ".out", "w", stdout);
#endif
    rep (i, 0, 30)
        hh[i] = mm[i] = -1;
    rep (i, 0, 23) rep (j, 0, 59) {
        int x = w[i / 10] + w[i % 10] + w[j / 10] + w[j % 10];
        hh[x] = i;
        mm[x] = j;
    }    

    int n;
    scanf("%d", &n);
    if (hh[n] < 0)
        puts("Impossible");
    else
        printf("%02d:%02d\n", hh[n], mm[n]);

}