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

const int N = 502;
int qwq[N];
int main() {
    int n, a, b;
    scanf("%d%d%d", &n, &a, &b);
    rep (i, 1, n)
        scanf("%d", &qwq[i]);

    long long p = 0, q = 0;
    while (true) {
        ++q;
        std::random_shuffle(qwq + 1, qwq + n + 1);
        int s = 0;
        bool ok = false;
        rep (i, 1, n) {
            s += qwq[i];
            if (s > b)
                break;
            if (s > a) {
                ok = true;
                break;
            }
        }
        if (ok)
            ++p;
        if (q % 10000 == 0)
            ccc(p, q, (double)p/q);
    }

    return 0;
}