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


const char *s1 = "0COFFEE", *s2 = "0CHICKEN";
const ll mxlen = 1000000000010ll;
ll f[505];
void put(int n, ll k, int c) {
    ccc(n,k,c);
    if (n == 1) {
        rep (i, k, std::min(6ll, k + c - 1)) {
            putchar(s1[i]);
        }
    } else if (n == 2) {
        rep (i, k, std::min(7ll, k + c - 1))
            putchar(s2[i]);
    } else {
        ll a = f[n - 2], r = k + c - 1;
        if (r <= a) {
            ccc("C1", k, a, r);
            put(n - 2, k, c);
        }
        else if (k > a) {
            ccc("C2", k, a);
            put(n - 1, k - a, c);
        }
        else { // k <= a < r
            ccc("C3");
            int lc = a - k + 1;
            put(n - 2, k, lc);
            put(n - 1, 1, c - lc);
        }
    }
}

int main() {
    f[1] = 6;
    f[2] = 7;
    rep (i, 3, 500) {
        f[i] = std::min(mxlen, f[i - 2] + f[i - 1]);
        ccc(i, f[i]);
    }
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        ll k;
        scanf("%d%lld", &n, &k);
        put(n, k, 10);
        putchar('\n');
    }
}