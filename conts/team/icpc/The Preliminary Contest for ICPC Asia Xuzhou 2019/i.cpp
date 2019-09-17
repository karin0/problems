#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
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

cint N = 100003;
int c[N];
int n;
inline void add(int i) {
    for (; i <= n; i += i & -i)
        ++c[i];
}
inline int qry(int i) {
    int res = 0;
    for (; i; i -= i & -i)
        res += c[i];
    return res;
}

int pos[N], ans[N];
std::vector<int> v1[N];
struct S {
    int r, *ans;
    S() {}
    S(int r, int *p) : r(r), ans(p) {}
};
std::vector<S> v2[N];
int main() {
    int m;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        int x;
        scanf("%d", &x);
        pos[x] = i;
    }
    rep (i, 1, n) {
        int l = pos[i];
        for (int j = i << 1; j <= n; j += i) {
            int r = pos[j];
            if (l < r)
                v1[l].push_back(r);
            else
                v1[r].push_back(l);
        }
    }
    rep (i, 1, m) {
        int l, r;
        scanf("%d%d", &l, &r);
        v2[l].push_back(S(r, &ans[i]));
    }
    per (i, n, 1) {
        for (int r : v1[i])
            add(r);
        for (auto &x : v2[i])
            *x.ans = qry(x.r);
    }
    rep (i, 1, m)
        printf("%d\n", ans[i]);
}
