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
 
int main() {
    // freopen("halfnice.in", "r", stdin);
    sieve();
    int t;
    scanf("%d", &t);
    rep (ks, 1, t)  {
        ll a, b;
        scanf("%lld%lld", &a, &b);
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
        // l = t;
        int u = solve(t, r);
        while (!u) {
            --t;
            if ((ll)t * ww + ww - 1 < a)
                break;
            u = solve(t, ww - 1);
        }
        printf("Case %d: ", ks);
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