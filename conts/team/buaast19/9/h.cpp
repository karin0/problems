#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
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

const int N = 100002, z = 256;

ll f[N][z];

inline int cv(char c) {
    return isdigit(c) ? c - '0' : (c - 'A' + 10);
}
int main() {
    int n, x;
    char s[3];
    scanf("%d", &n);
    rep (i, 1, n) {
        scanf("%s", s);
        x = cv(s[0]) * 16 + cv(s[1]);
        rep (j, 0, 255)
            f[i][j] = std::max(f[i - 1][j] + ((i - 1 - j + 1 - 1) ^ x), f[i - 1][j - 1]);
    }
    printf("%lld\n", *std::max_element(f[n], f[n] + z));
}