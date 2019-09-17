#include <cstdio>
#include <algorithm>
#include <iostream>
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

const int N = 500003;
int a[N]; //, slc[N], src[N];
// ll f[N], g[N];
struct S {
    int x, c;
} b[N];

int n, cnt;
int cal(int k) {
    int lc = 0, mn = 0, mx = 0;
    ll ck = 0;
    lc = 0;
    re (i, 1, cnt) {
        lc += b[i].c;
        // slc[i] = lc;
        ll nck = ck + (ll)(b[i + 1].x - b[i].x) * lc;
        // f[i] = nck;
        if (nck >= k) {
            mn = b[i].x + (k - ck) / lc;
            ccc(mn);
            break;
        }
        ck = nck;
    }
    if (!mn)
        mn = b[cnt].x + (k - ck) / n;

    lc = 0;
    ck = 0;
    per (i, cnt, 2) {
        lc += b[i].c;
        // src[i] = lc;
        ll nck = ck + (ll)(b[i].x - b[i - 1].x) * lc;
        ccc(i, ck, nck, lc);
        // g[i] = nck;
        if (nck >= k) {
            mx = b[i].x - (k - ck) / lc;
            ccc(mx);
            break;
        }
        ck = nck;
    }
    ccc(k, ck, n);
    if (!mx)
        mx = b[1].x - (k - ck) / n;
    ccc(mn, mx);
    return mx - mn;
}

int sol(int k) {
    if (n == 1)
        return 0;
    std::sort(a + 1, a + n + 1);
    int lx = a[1], lc = 1;
    cnt = 0;
    rep (i, 2, n) {
        if (a[i] == a[i - 1]) {
            ++lc;
        } else {
            b[++cnt].x = lx;
            b[cnt].c = lc;
            lx = a[i];
            lc = 1;
        }
    }
    b[++cnt].x = lx;
    b[cnt].c = lc;
   //  rep (i, 1, cnt)
    //    ccc(i, b[i].x, b[i].c);
    if (cnt == 1)
        return 0;

    int t = cal(k);
    ccc(t);
    if (t <= 0) {
        int l = 0, r = k; // [l, r)
        while (r - l > 1) {
            int mid = (l + r) >> 1;
            int ret = cal(mid);
            if (ret <= 0)
                r = mid;
            else
                l = mid;
        }
        int ret = cal(l);
        if (ret == 2)
            return (k - l) ? 0 : 2;
        else
            return ret;
    } else
        return t;
}

int brt(int k) {
    while (k--) {
        std::sort(a + 1, a + n + 1);
        --a[n];
        std::sort(a + 1, a + n + 1);
        ++a[1];
    }
    std::sort(a + 1, a + n + 1);
    return a[n] - a[1];
}

int main() {
    int k;
    while (scanf("%d%d", &n, &k) == 2) {
        rep (i, 1, n)
            scanf("%d", &a[i]);
        int ans = sol(k);
        /*
        int ab = brt(k);
        ccc(ans, ab);
        if (ans != ab)
           return 1;*/
        printf("%d\n", ans);
    }
}
