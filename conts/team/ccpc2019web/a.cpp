#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
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
    int T;
    scanf("%d", &T);
    while (T--) {
        ll a, b, c = 0;
        scanf("%lld%lld", &a, &b);
        per (i, 31, 0) {
            int ai = (a >> i) & 1, bi = (b >> i) & 1;
            // ccc(i, ai, bi);
            if (!(ai & bi))
                continue;
            if (!((ai ^ 1) & (bi ^ 1)))
                c += 1ll << i;
        }
        if (!c)
            ++c;
        printf("%lld\n", c);
    }
}