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

char s[200003];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        ll a, b;
        scanf("%d%lld%lld%s", &n, &a, &b, s + 1);
        ll ans = n * a + (n + 1) * b;
        int la1 = 0;
        rep (i, 1, n) {
            s[i] -= '0';
            if (s[i]) {
                ans += b;
                if (!s[i - 1])
                    ans += b;
                if (la1) {
                    int len = i - la1 - 1;
                    if (len > 1)
                        ans += std::min(2 * a, (len - 1) * b);
                }
                la1 = i;
            }
        }
        if (la1)
            ans += 2 * a;
        printf("%lld\n", ans);
    }

}