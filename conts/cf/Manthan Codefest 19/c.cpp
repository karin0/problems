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

int a[1004][1004], b[4][4] = {
    {8, 9, 1, 13},
    {3, 12, 7, 5},
    {0, 2, 4, 11},
    {6, 10, 15, 14}
};
void ff(int x, int y, int t) {
    re (i, 0, 4) re (j, 0, 4)
        a[x + i][y + j] = b[i][j] + t;
}
int main() {
    int n;
    scanf("%d", &n);
    int m = n >> 2, t = 0;
    re (i, 0, m) re (j, 0, m) {
        ff(i << 2, j << 2, t);
        t += 16;
    }
    /*
    re (i, 0, n) {
        int s1 = 0, s2 = 0;
        re (j, 0, n) {
            s1 ^= a[i][j];
            s2 ^= a[j][i];
        }
        ccc(i, s1, s2);
    }*/
    re (i, 0, n) {
        re (j, 0, n)
            printf("%d%c", a[i][j], j == n - 1 ? '\n' : ' ');
    }
}