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

const int N = 200003;
int aa[N * 2], *pos[N];
int main() {
    int *a = aa + N;
    int n, m;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        a[i] = i;
        pos[i] = &a[i];
    }
    while (m--) {
        int x;
        scanf("%d", &x);
        *pos[x] = 0;
        pos[x] = a;
        *a = x;
        --a;
    }
    rep (i, 1, n) {
        while (!*a)
            ++a;
        printf("%d\n", *a);
        ++a;
    }
}