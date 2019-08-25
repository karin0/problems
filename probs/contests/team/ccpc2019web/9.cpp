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

ll f[32][32][77];
inline ll gf(int i, int j, int k) {
    return i <= j ? f[i][j][k] : f[j][i][k];
}
int main() {
    // f[0][0][0] = 1;
    // rep (i, 1, 30)
    //     f[0][i][0] = 1;
    int n = 2;
    rep (i, 1, n) {
        rep (j, i, n) {
            f[i][j][1] = 1ll << (i * j - 1);
            ccc(i, j, 1, f[i][j][1]);
            for (int k = 3; k <= i + j - 1; k += 2) {
                f[i][j][k] = gf(i - 1, j, k);
                re (l, 1, k) {
                    f[i][j][k] += f[i][j][l] + f[i][j][k - l];
                }
                if (f[i][j][k])
                    ccc(i, j, k, f[i][j][k]);
            }
        }
    }
}
