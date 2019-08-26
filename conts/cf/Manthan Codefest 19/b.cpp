#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
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

const int N = 2003;
int a[N];
std::set<int> s;
std::vector<int> vec;
int main() {
    int n;
    scanf("%d", &n);
    int ans = n - 1;
    rep (i, 1, n) {
        scanf("%d", &a[i]);
        s.insert(a[i]);
        if (s.size() == i)
            ans = std::min(ans, n - i);
    }
    if (!ans)
        return puts("0"), 0;
    s.clear();
    per (i, n, 1) {
        s.insert(a[i]);
        if (s.size() == n - i + 1)
            ans = std::min(ans, i - 1);
    }
    if (!ans)
        return puts("0"), 0;
    s.clear();
    rep (i, 1, n) {
        if (s.count(a[i]))
            break;
        s.insert(a[i]);
        int len = i;
        vec.clear();
        for (int j = n; j >= i + 2; --j) {
            if (s.count(a[j]))
                break;
            s.insert(a[j]);
            vec.push_back(a[j]);
            ++len;
            ans = std::min(ans, n - len);
        }
        for (int x : vec)
            s.erase(x);
    }
    printf("%d\n", ans);
}