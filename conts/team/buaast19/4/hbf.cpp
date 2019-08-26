#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef long long ll;


const int N = 10000002;


ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    // freopen("halfnice.in", "r", stdin);
    int t;
    scanf("%d", &t);
    rep (ks, 1, t)  {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        printf("Case %d: ", ks);

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
    }

    return 0;
}
