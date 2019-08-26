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

typedef unsigned __int128 lll;

const int mo = 1000000007;
int a, b;
lll cal(ll n) {
    lll ln = n;
    lll t = ln * ln * (ln * b + (ln - 1) * a);
    if (!(n & 1)) {
        lll h = n >> 1;
        t = std::min(t, 18 * h * h * a + 7 * cal(h));
    }
    return t;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll n;
        scanf("%I64d%d%d", &n, &a, &b);
        printf("%d\n", int(cal(n) % mo));
    }
}