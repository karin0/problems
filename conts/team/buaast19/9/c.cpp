#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
#include <random>
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

const int M = 1000000000;

std::random_device rad;
std::mt19937 gen(rad());

int rd(int l, int r) {
    std::uniform_int_distribution<int> uid(l, r);
    return uid(gen);
}

/*
int ax = 51145810, ay = 99122673, cnt;
ll dis(ll x1, ll y1, ll x2, ll y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
bool chk(int x, int y) {
    static ll pd = LLONG_MAX;
    ll d = dis(x, y, ax, ay); // (ll)(x - ax) * (x - ax) + (ll)(y - ay) * (y - ay);
    bool res = d < pd;
    pd = d;
    if (++cnt == 1)
        return 0;
    // ccc(x, y, d, pd, res);
    return res;
}
*/
bool chk(int x, int y) {
    printf("%d %d\n", x, y);
    fflush(stdout);
    int t;
    scanf("%d", &t);
    return t;
}
inline int lmid(int l, int r) {
    return (l + r) >> 1;
}
inline int rmid(int l, int r) {
    return (l + r + 1) >> 1;
}

const int N = 1000000;
int main() {
    // int x, y;
    int l = 0, r = M;
    int la = rd(l, r);
    chk(la, 0);
    while (r > l) {
        int p;
        do
            p = rd(l, r);
        while (p == la);
        bool res = chk(p, 0);
        if (p < la) {
            if (res)
                r = rmid(p, la) - 1;
            else
                l = rmid(p, la);
        } else {
            if (res)
                l = lmid(la, p) + 1;
            else
                r = lmid(la, p);
        }
        la = p;
    }
    int x = l;
    l = 0, r = M;
    la = rd(l, r);
    chk(0, la);
    while (r > l) {
        int p;
        do
            p = rd(l, r);
        while (p == la);
        bool res = chk(0, p);
        if (p < la) {
            if (res)
                r = rmid(p, la) - 1;
            else
                l = rmid(p, la);
        } else {
            if (res)
                l = lmid(la, p) + 1;
            else
                r = lmid(la, p);
        }
        la = p;
    }
    int y = l;
    printf("A %d %d\n", x, y);
}