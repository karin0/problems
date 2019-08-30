#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>
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

const int N = 4003, m1 = 21332711, m2 = 19260817, m3 = 42313339;
const int b = 4003;
char s1[N], s2[N];
int pw1[300], pw2[300], pw3[300], pre1[N], pre2[N], pre3[N];
bool h1[m1], h2[m2], h3[m3], vis[300];
void add(int &x, const int v, const int m) {
    if ((x += v) >= m)
        x -= m;
}
int main() {
    scanf("%s%s", s1 + 1, s2 + 1);
    int n1 = strlen(s1 + 1);
    int n2 = strlen(s2 + 1);
    pw1['a' - 1] = 1;
    pw2['a' - 1] = 1;
    pw3['a' - 1] = 1;
    rep (i, 'a', 'z') {
        pw1[i] = (ll)pw1[i - 1] * b % m1;
        pw2[i] = (ll)pw2[i - 1] * b % m2;
        pw3[i] = (ll)pw3[i - 1] * b % m3;
    }
    rep (i, 1, n2) {
        int ha1 = 0, ha2 = 0, ha3 = 0;
        vis[s2[i]] = 1;
        rep (j, i, n2) {
            add(ha1, pw1[s2[j]], m1);
            add(ha2, pw2[s2[j]], m2);
            add(ha3, pw3[s2[j]], m3);
            h1[ha1] = 1;
            h2[ha2] = 1;
            h3[ha3] = 1;
        }
    }
    bool is0 = true;
    rep (i, 1, n1) {
        pre1[i] = pre1[i - 1] + pw1[s1[i]];
        pre2[i] = pre2[i - 1] + pw2[s1[i]];
        pre3[i] = pre3[i - 1] + pw3[s1[i]];
        if (pre1[i] >= m1)
            pre1[i] -= m1;
        if (pre2[i] >= m2)
            pre2[i] -= m2;
        if (pre3[i] >= m3)
            pre3[i] -= m3;
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
            if (j > n1)
                break;
            int t1 = pre1[j] - pre1[i - 1];
            if (t1 < 0)
                t1 += m1;
            int t2 = pre2[j] - pre2[i - 1];
            if (t2 < 0)
                t2 += m2;
            int t3 = pre3[j] - pre3[i - 1];
            if (t3 < 0)
                t3 += m3;
            if (h1[t1] && h2[t2] && h3[t3]) {
                printf("%d\n", l);
                return 0;
            }
        }
    }
    return puts("0"), 0;
}