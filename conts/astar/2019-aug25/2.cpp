#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cfloat>
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

const double eps = 1e-8;
inline bool equ(double a, int b) {
    return fabs(a - b) <= eps;
}

struct S {
    double x, y;
    void read() {
        scanf("%lf%lf", &x, &y);
    }
    double move() {
        double &t = (equ(x, 0) || equ(x, 1)) ? y : x;
        double ot = t;
        t = t <= 0.5 ? 0 : 1;
        return fabs(ot - t);
    }
    double pos() const {
        if (equ(y, 0)) return x;
        if (equ(x, 1)) return 1 + y;
        if (equ(y, 1)) return 3 - x;
        // if (equ(x, 0))
        return 4 - y;
    }
    double dis(const S rhs) const {
        double t = fabs(pos() - rhs.pos());
        return std::min(t, 4 - t);
    }
    S flip() const {
        return (S){1 - x, 1 - y};
    }
};
bool com(const S a, const S b) {
    if (equ(a.x, 0) && equ(b.x, 0)) return true;
    if (equ(a.x, 1) && equ(b.x, 1)) return true;
    if (equ(a.y, 0) && equ(b.y, 0)) return true;
    if (equ(a.y, 1) && equ(b.y, 1)) return true;
    return false;
}

S a[4];
double ans;
void solve(S a, S b, S c, S d) {
    ans = std::min(ans, std::min(c.dis(a.flip()) + d.dis(b.flip()), c.dis(b.flip()) + d.dis(b.flip())));
}
void solve() {
    solve(a[0], a[1], a[2], a[3]);
    solve(a[0], a[2], a[1], a[3]);
    solve(a[0], a[3], a[1], a[2]);
    solve(a[1], a[2], a[0], a[3]);
    solve(a[1], a[3], a[0], a[2]);
    solve(a[2], a[3], a[0], a[1]);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        rep (i, 0, 3)
            a[i].read();
        bool comm = true;
        rep (i, 0, 3) re (j, 0, i) if (!com(a[i], a[j]))
            comm = false;
        ans = DBL_MAX;
        if (comm) {
            rep (i, 0, 3) {
                double tans = ans;
                S t = a[i];
                double r = a[i].move();
                solve();
                a[i] = t;
                if (ans < tans)
                    ans = std::min(tans, ans + r);
                else
                    ans = tans;
            }
        } else
            solve();
        printf("%.12f\n", ans);
    }

}