#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>
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

const int N = 1003;
struct S {
    int x, y;
    S() {}
    S(int x, int y) : x(x), y(y) {}
    bool operator < (const S &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    bool operator == (const S &rhs) const {
        return x == rhs.x && y == rhs.y;
    }
    int count() const;
} a[N], aa[N * N];
std::multiset<S> ms;
int S::count() const {
    int xx = x, yy = y;
    if ((std::abs(xx) & 1) || (std::abs(yy) & 1) )
        return 0;
    return ms.count(S(x / 2, y / 2));
}

int main() {
    int n;
    scanf("%d", &n);
    int siz = 0, mc = 1;
    rep (i, 1, n) {
        scanf("%d%d", &a[i].x, &a[i].y);
        mc = std::max(mc, int(ms.count(a[i])) + 1);
        ms.insert(a[i]);
    }
    rep (i, 1, n)
        re (j, 1, i) {
            if (a[i] == a[j])
                continue;
            aa[++siz] = S(a[i].x + a[j].x, a[i].y + a[j].y);
        }
    if (!siz)
        return puts("0"), 0;
    std::sort(aa + 1, aa + siz + 1);
    int cc = 1, ans = n - mc;
    rep (i, 2, siz) {
        if (aa[i] == aa[i - 1]) {
            ++cc;
        } else {
            ans = std::min(ans, n - (cc << 1) - aa[i - 1].count());
            cc = 1;
        }
    }
    ans = std::min(ans, n - (cc << 1) - aa[siz].count());
    printf("%d\n", ans);
}
