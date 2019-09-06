#include <bits/stdc++.h>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;

using std::abs;
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

const int N = 3003, mo = 1000000007;

int c[N], f[N][2];

inline void add(int &x, int v) {
    if ((x += v) >= mo)
        x -= mo;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        re (i, 1, n) {
            scanf("%d", &c[i]);
            f[i][0] = f[i][1] = 0;
        }
        f[1][0] = 0;
        f[1][1] = c[1] - 1;
        rep (i, 2, n) {
            f[i][0] = f[i - 1][0];
            f[i][1] = (ll)f[i - 1][0] * (c[i] - 1) % mo;
            if (c[i] == c[i + 1])
                add(f[i][0], f[i - 1][1]);
            else
                add(f[i][1], f[i - 1][1]);
            /*
            if (c[i] < c[i + 1]) {
                add(f[i + 1][0], f[i][0]);
                add(f[i + 1][0], f[i][0]);
            } else if (c[i] == c[i + 1]) {
                add(f[i + 1][1], f[i][0]);
                add(f[i + 1][0], f[i][0]);
            } else {

            }
            re (j, 0, n) {

            }*/
        }
        printf("%d\n", f[n][0] + f[n][1]);
    }
}
