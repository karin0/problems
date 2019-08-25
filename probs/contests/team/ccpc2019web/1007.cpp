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

char a[1111][1111];
void ff(int k) {
    if (k == 1) {
        a[0][0] = a[0][1] = a[1][1] = 'C';
        a[1][0] = 'P';
        return;
    }
    ff(k - 1);
    int n = 1 << (k - 1);
    re (i, 0, n) re (j, 0, n) {
        a[i][n + j] = a[n + i][n + j] = a[i][j];
        a[n + i][j] = a[i][j] == 'C' ? 'P' : 'C'; 
    }
} 
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int k;
        scanf("%d", &k);
        ff(k);
        int n = 1 << k;
        re (i, 0, n)  {
            re (j, 0, n)
                putchar(a[i][j]);
            putchar('\n');
        }
    }
}