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

const int N = 103;
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
    ll operator * (const S &rhs) const {
        return (ll)x * rhs.y - (ll)y * rhs.x;
    }
    ll operator / (const S &rhs) const {
        return (ll)x * rhs.x + (ll)y * rhs.y;
    }
    ll norm2() const {
        return (ll)x * x + (ll)y * y;
    }
    bool operator < (const S &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
} a[N], c[N];

bool sol() {
    int n;
    scanf("%d", &n);
    rep (i, 1, n)
        a[i].read();
    if (n == 2)
        return false;
    std::sort(a + 1, a + n + 1);
    int siz = 0;
    rep (i, 1, n) {
        const S &p = a[i];
        while (siz > 1 && (c[siz] - c[siz - 1]) * (p - c[siz - 1]) < 0)
            --siz;
        c[++siz] = p;
    }
    int os = siz;
    per (i, n - 1, 1) {
        const S &p = a[i];
        while (siz > os && (c[siz] - c[siz - 1]) * (p - c[siz - 1]) < 0)
            --siz;
        c[++siz] = p;
    }
    ll t = -1;
    re (i, 1, siz) {
        ll r = (c[i + 1] - c[i]).norm2();
        if (t < 0)
            t = r;
        else if (t != r)
            return false;
    }
    t = -1;
    re (i, 2, siz) {
        ll r = (c[i + 1] - c[i]) * (c[i - 1] - c[i]);
        if (t < 0)
            t = r;
        else if (t != r)
            return false;
    }
    return true;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        puts(sol() ? "YES" : "NO");
    }

}