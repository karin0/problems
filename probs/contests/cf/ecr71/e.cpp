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

int main() {
    putchar('?');
    rep (i, 1, 100)
        printf(" %d", i);
    putchar('\n');
    fflush(stdout);
    int a, b;
    scanf("%d", &a);
    putchar('?');
    rep (i, 1, 100)
        printf(" %d", i << 7);
    putchar('\n');
    fflush(stdout);
    scanf("%d", &b);
    int t = (1 << 7) - 1;
    printf("! %d\n", (b & t) + (a & (t << 7)));
    fflush(stdout);
}