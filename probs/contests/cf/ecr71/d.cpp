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

const int N = 300003, mo = 998244353;
std::pair<int, int> a[N];
int n, fac[N];
// int a[N], b[N];
int cal(int* t) {
    std::sort(t + 1, t + n + 1);
    int cnt = 1;
    ll ans = 1;
    rep (i, 1, n) {
        if (t[i] == t[i - 1])
            ++cnt;
        else {
            ans = ans * fac[cnt] % mo;
            cnt = 1;
        }
    }
    ans = ans * fac[cnt] % mo;
    return ans;
}
int cal(std::pair<int, int>* t) {
    std::sort(t + 1, t + n + 1);
    int cnt = 1;
    ll ans = 1;
    rep (i, 1, n) {
        if (i > 1 && t[i].second < t[i - 1].second)
            return 0;
        if (t[i] == t[i - 1])
            ++cnt;
        else {
            ans = ans * fac[cnt] % mo;
            cnt = 1;
        }
    }
    ans = ans * fac[cnt] % mo;
    return ans;
}
int t[N];
int main() {
    scanf("%d", &n);
    fac[0] = 1;
    rep (i, 1, n) {
        fac[i] = (ll)fac[i - 1] * i % mo;
        scanf("%d%d", &a[i].first, &a[i].second);
        t[i] = a[i].first;
    }
    ll ans = fac[n] - cal(t);
    if (ans < 0)
        ans += mo; 
    rep (i, 1, n)
        t[i] = a[i].second;
    ans -= cal(t);
    if (ans < 0)
        ans += mo; 
    ans += cal(a);
    if (ans >= mo)
        ans -= mo;
    printf("%lld\n", ans);
}