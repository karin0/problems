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

int n, p, q, m;
uint SA, SB, SC;
inline uint rng61() {
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    uint t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}

uint sta[5000003];
int siz;
inline uint pop() {
    if (siz > 1)
        return sta[--siz];
    else if (siz == 1)
        return --siz;
    else
        return 0;
}
inline uint push(uint x) {
    if (siz)
        x = std::max(x, sta[siz]);
    sta[++siz] = x;
    return x;
}

int main() {
    int T;
    scanf("%d", &T);
    rep (ks, 1, T) {
        unsigned long long ans = 0;
        scanf("%d%d%d%d%u%u%u", &n, &p, &q, &m, &SA, &SB, &SC);
        siz = 0;
        rep (i, 1, n) {
            uint rr;
            if (rng61() % (p + q) < p)
                rr = push(rng61() % m + 1);
            else
                rr = pop();
            ans ^= (unsigned long long)i * rr;
        }
        printf("Case #%d: %llu\n", ks, ans);
    }
}
