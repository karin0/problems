#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
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

cint N = 1000003;
bool np[N];
int phi[N], pri[N], pcnt;
inline void sieve() {
    cint n = 1000000;
    np[0] = np[1] = true;
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i, phi[i] = i - 1;
        for (int j = 1; j <= pcnt; ++j) {
            ll v = (ll)pri[j] * i;
            if (v > n)
                break;
            np[v] = true;
            if (i % pri[j] == 0) {
                phi[v] = phi[i] * pri[j];
                break;
            } else
                phi[v] = phi[i] * (pri[j] - 1);
        }
    }
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

inline int qpow(ll a, int n, int m) {
    ll res = 1;
    for (; n; n >>= 1, a = a * a % m)
        if (n & 1)
            res = res * a % m;
    return res;
}

inline int qpow(int a, int n) {
    int res = 1;
    for (; n; n >>= 1, a = a * a)
        if (n & 1)
            res = res * a;
    return res;
}

int qaq[20];

int cal(int a, int b, int m) {
    if (b == 0)
        return 1;
    int p = phi[m];
    if (b - 1 <= 10 && qaq[b - 1] && qaq[b - 1] < p)
        return qpow(a, qaq[b - 1], m);
    else {
        int rr = p == 1 ? 0 : cal(a, b - 1, p);
        if (gcd(a, m) == 1)
            return qpow(a, rr, m);
        else
            return qpow(a, rr + p, m);
    }
}

// int q[1000003];
int main() {
    sieve();
    // rep (i, 1, 100)
    //     ccc(i, phi[i]);
    int T;
    scanf("%d", &T);
    qaq[0] = 1;
    while (T--) {
        int a, b, m;
        scanf("%d%d%d", &a, &b, &m);
        if (m == 1) {
            puts("0");
            continue;
        }
        int p = m + 2, i;
        for (i = 1; i <= 10; ++i) {
            int t = qaq[i - 1];
            if (t <= std::log(p) / std::log(a))
                qaq[i] = qpow(a, t);
            else
                break;
        }
        for (; i <= 10; ++i)
            qaq[i] = 0;
        // rep (j, 1, 10)
        //    ccc(j, qaq[j]);
        printf("%d\n", cal(a, b, m));
    }
}
