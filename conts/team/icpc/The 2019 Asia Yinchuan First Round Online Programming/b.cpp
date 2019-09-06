#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
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

struct S {
    int x, y;
    S() {}
    S(int x, int y) : x(x), y(y) {}
    void read() {
        scanf("%d%d", &x, &y);
    }
    S operator - (const S &rhs) const {
        return S(x - rhs.x, y - rhs.y);
    }
    int operator * (const S &rhs) const {
        return x * rhs.x + y * rhs.y;
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
} a[54];
inline int sq(const int x) {
    return x * x;
}
inline double ang(const S &p, const S &q) {
    return acos(double(p * q) / ((double)p.len() * q.len()));
}

const double pi = acos(-1);

int main() {
    int T;
    S q;
    scanf("%d", &T);
    rep (ks, 1, T) {
        int n;
        scanf("%d", &n);
        re (i, 0, n)
            a[i].read();
        a[n] = a[0];
        a[n + 1] = a[1];
        q.read();
        double ans = 0;
        re (i, 0, n) {
            double r = (a[i + 1] - q).len();
            double t = pi - ang(a[i] - a[i + 1], a[i + 2] - a[i + 1]);
            // ccc(i, r, t);
            ans += r * t;
        }
        printf("Case #%d: %.3f\n", ks, ans);
    }
}
