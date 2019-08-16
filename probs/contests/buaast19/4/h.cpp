#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;


const int N = 10000002;

bool np[N];
int pri[N], f[N], pcnt;
inline void sieve() {
    int n = 10000000;
    for (int i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i, f[i] = i;
        for (int j = 1; j <= pcnt; ++j) {
            ll v = (ll)i * pri[j];
            if (v > n)
                break;
            np[v] = true;
            f[v] = pri[j];
            if (i % pri[j] == 0)
                break;
        }
    }
}

int solve(int l, int r) {
    int t = l, lp = 0, ans = 0;
    while (t > 1) {
        int p = f[t];
        t /= p;
        if (p == lp)
            continue;
        lp = p;
        ans = std::max(ans, r / p * p);
    }
    // printf("l=%d r=%d ans=%d\n", l,r,ans);
    return ans;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    freopen("halfnice.in", "r", stdin);
    sieve();
    int t;
    scanf("%d", &t);
    rep (ks, 1, t)  {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        printf("Case %d: ", ks);

tag:

        if (b <= 300) {

        bool fail = true;
        for (long long i = b; i >= a; --i) {
            int w = 0;
            ll t = i;
            while (t)
                t /= 10, ++w;
            int rw = w - (w >> 1);
            int r = 0, ww = 1;
            t = i;
            while (rw--) {
                ll nt = t / 10;
                r += (t - nt * 10) * ww;
                ww = ww * 10;
                t = nt;
            }
            if (!t || !r)
                continue;
            if (gcd(t, r) > 1) {
                fail = false;
                printf("%lld\n", i);
                break;
            }
        }
        if (fail)
            puts("impossible");

        continue;
        }

        int w = 0;
        ll t = b;

        while (t)
            t /= 10, ++w;
        int rw = w - (w >> 1);
        int r = 0, ww = 1;
        t = b;
        while (rw--) {
            ll nt = t / 10;
            r += (t - nt * 10) * ww;
            ww = ww * 10;
            t = nt;
        }

        if (t == 1) {
            if (b < 100) {
                puts("impossible");
                continue;
            }
            b = (ll)t * ww - 1;
            goto tag;
        }

        int oo = t, ow = 1;
        while (oo)
            oo /= 10, ow *= 10;

        // printf("t=%lld ow=%d oo=%d r=%d\n", t,ow,oo,r);
        if (t == ow / 10 && r < 2) { 
            ll ans;
                ans = (ll)t * ww - 1;
            if (ans < a) {
                puts("impossible");
                continue;
            }
            printf("%lld\n", ans);
            continue;
        }

        // l = t;
        int u = solve(t, r);
        while (!u) {
            --t;
            if ((ll)t * ww + ww - 1 < a)
                break;
            u = solve(t, ww - 1);
        }
        if (!u) {
            puts("impossible");
            continue;
        }
        ll ans = u + (ll)ww * t;
        if (ans < a) {
            puts("impossible");
            continue;
        }
        printf("%lld\n", ans);
    }

    return 0;
}
