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

bool chk(ll a, ll b, ll c, ll d) {
    if (a == b) {
        if (c == a && d == b)
            return true;
        return false;
    }
    if (c == d)
        return false;
    ll t = (c - d) / (a - b);
    if (t * (a - b) != c - d)
        return false;
    if (!t)
        return false;
    int cnt = 0;
    while (t) {
        if (t & 1) {
            ++cnt;
            if (cnt > 1)
                return false;
        }
        t >>= 1;
    }
    ll p = (c - b) / (a - b);
    ll q = (d - a) / (b - a);
    if (p <= 0)
        return false;
    if (q <= 0)
        return false;
    if (p * (a - b) != c - b)
        return false;
    if (q * (b - a) != d - a)
        return false;
    return true;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll a, b, c, d;
        scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
        if (chk(a, b, c, d)) {
            puts("Yes");
            while (a != c || b != d) {
                ll tb = 2 * b - a;
                if (chk(a, tb, c, d))
                    b = tb, putchar('A');
                else
                    a = 2 * a - b, putchar('B');
            }
            putchar('\n');
        } else
            puts("No");
    }
}
