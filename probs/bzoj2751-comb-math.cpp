#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x)
    #define ccf(x)
    #define cccc(...)
#endif
typedef long long ll;

const int K = 100003, mo = 1000000007;
int qpow(ll a, int n) {
    ll res = 1;
    for (; n; n >>= 1, a = a * a % mo)
        if (n & 1)
            res = res * a % mo;
    return res;
}
int n, m, k;
struct pair_t {
    int i, v;
    bool operator < (const pair_t &rh) const {
        return i < rh.i || (i == rh.i && v < rh.v); // ****
    }
    bool operator != (const pair_t &rh) const {
        return i != rh.i || v != rh.v;
    }
} r[K];
int main() {
    static int i, x, t;
    static ll ans = 1;
    scanf("%d%d%d", &n, &m, &k);
    t = x = ((ll)n * (n + 1) >> 1ll) % mo;
    if (!k) {
        printf("%d\n", qpow(x, m));
        return 0;
    }
    rep (i, 1, k)
        scanf("%d%d", &r[i].i, &r[i].v);
    std::sort(r + 1, r + k + 1);
    rep (i, 1, k) {
        const pair_t &q = r[i];
        if (i == 1 || q != r[i - 1])
            if ((t -= q.v) < 0)
                t += mo;
        if (i == k || r[i + 1].i != q.i) {
            ans = ans * t % mo;
            t = x;
            --m;
        }
    }
    printf("%d\n", (int)(ans * qpow(x, m) % mo));
    // use ioo to get wa

    return 0;
}

