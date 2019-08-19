#include <cstdio>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
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

const int N = 100003, mx = 100000;

std::multiset<int> s;
struct S {
    int x, y;
} a[N];
int f[N], sx[N], r;

inline void ins0(int y) {
    if (y < 0 || y > mx)
        return;
    s.erase(s.find(f[y]));
    s.insert(++f[y]);
}
inline void del0(int y) {
    if (y < 0 || y > mx)
        return;
    s.erase(s.find(f[y]));
    s.insert(--f[y]);
}
inline void ins(int y) {
    ins0(y); ins0(y-r); ins0(y+r);
}
inline void del(int y) {
    del0(y); del0(y-r); del0(y+r);
}

std::vector<int> ve[N];
int main () {
    int n;
    scanf("%d%d", &n, &r);
    int mxx = 0;
    rep (i, 1, n) {
        int x, y;
        scanf("%d%d", &x, &y);
        ve[x].push_back(y);
        mxx = std::max(mxx, x);
        ++sx[x];
        ++f[y];
        if (y - r >= 0)
            ++f[y - r];
        if (y + r <= mx)
            ++f[y + r];
    }
    rep (i, 0, mx) {
        s.insert(f[i]);
        // ccc(i, f[i]);
    }
    int ans = 0;
    rep (i, 0, mxx) {
        for (auto y : ve[i])
            del(y);
        int ss = sx[i];
        if (i - r >= 0) {
            ss += sx[i - r];
            for (auto y : ve[i - r])
                del(y);
        }
        if (i + r <= mx) {
            ss += sx[i + r];
            for (auto y : ve[i + r])
                del(y);
        }
        //crep (j, 0, mx) {
        //    ccc("QAQ", i, j,  f[j]);
        //}
        // ccc(i, ss, *s.rbegin());
        ans = std::max(ans, ss + *s.rbegin());
        for (auto y : ve[i])
            ins(y);
        if (i - r >= 0)
            for (auto y : ve[i - r])
                ins(y);
        if (i + r <= mx)
            for (auto y : ve[i + r])
                ins(y);
    }
    printf("%d\n", ans);
}