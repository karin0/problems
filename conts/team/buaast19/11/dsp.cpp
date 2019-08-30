#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;
typedef unsigned long long ull;

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

const int N = 4003;
const ull b = 4003;
char s1[N], s2[N];
ull pw[300], pre[N], pr2[N];
bool vis[300];
std::unordered_set<ull> us;
int main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    int n1 = strlen(s1 + 1);
    int n2 = strlen(s2 + 1);
    pw['a' - 1] = 1ull;
    rep (i, 'a', 'z')
        pw[i] = pw[i - 1] * b;
    rep (i, 1, n2) {
        pr2[i] = pr2[i - 1] + pw[s2[i]];
        vis[s2[i]] = 1;
    }
    bool is0 = true;
    rep (i, 1, n1) {
        pre[i] = pre[i - 1] + pw[s1[i]];
        if (vis[s1[i]])
            is0 = false;
    }
    if (is0)
        return puts("0"), 0;
    int ml = std::min(n1, n2);
    per (l, ml, 1) {
        ull ha = 0;
        for (int i = 1; ; ++i) {
            int j = i + l - 1;
            if (j > n2)
                break;
            us.insert(pr2[j] - pr2[i - 1]);
        }
        for (int i = 1; ; ++i) {
            int j = i + l - 1;
            if (j > n1)
                break;
            if (us.count(pre[j] - pre[i - 1])) {
                printf("%d\n", l);
                return 0;
            }
        }
        us.clear();
    }
    return puts("0"), 0;
}