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

double p[140][140], f[10003][133];
int a[10003];
int main() {
    int m, n;
    while (scanf("%d", &m) == 1) {
        m = m * (m - 1) * (m - 2) / 6;
        rep (i, 1, m)  {
            rep (j, 1, m) {
                scanf("%lf", &p[i][j]);
                ccc(i, j, p[i][j]);
            }
            f[0][i] = 1;
        }
        f[0][0] = 1;
        scanf("%d", &n);
        rep (i, 1, n) {
            scanf("%d", &a[i]);
            ++a[i];
            f[i][0] = 0;
            rep (j, 1, m) {
                if (j == a[i - 1])
                    f[i][j] = f[i - 1][0] * p[j][a[i]];
                else
                    f[i][j] = f[i - 1][j] * p[j][a[i]];
                f[i][0] = std::max(f[i][0], f[i][j]);
            }
        }
        printf("%.6f\n", f[n][0]);
    }
}