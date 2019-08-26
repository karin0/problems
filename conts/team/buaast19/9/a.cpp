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

int cc[2000000];
int main() {
    int b;
    scanf("%d", &b);
    --b;
    int t, cnt = 0;
    for (t = 1; t * t < b; ++t)
        if (b % t == 0) {
            cc[cnt++] = t; 
            cc[cnt++] = b / t; 
        }
    if (t * t == b)
        cc[cnt++] = t;
    std::sort(cc, cc + cnt);
    re (i, 0, cnt)
        printf("%d%c", cc[i], i == cnt - 1 ? '\n' : ' ');
}