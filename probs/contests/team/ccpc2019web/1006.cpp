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

int pp[300003], *pos[100005];
int main() {
    int n, m;
    int *a = pp + 100000;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        scanf("%d", &a[i]);
        pos[a[i]] = &a[i];
    }
    while (m--) {
        int x;
        scanf("%d", &x);
        *pos[x] = 0;
        *a = x;
        pos[x] = a;
        --a;
    }
    int cnt = 0;
    while (cnt < n) {
        while (!*a)
            ++a;
        printf("%d ", *a);
        ++cnt;
        ++a;
    }
}