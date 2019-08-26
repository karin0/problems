#include <cstdio>
#include <algorithm>
#include <map>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;

const int N = 38;

ll a[N];
std::map<ll, int> f;
int main() {
    int n;
    ll sum;
    scanf("%d%lld", &n, &sum);
    re (i, 0, n)
        scanf("%lld", &a[i]);
    int nl = n >> 1, ul = 1 << nl, nr = n - nl;
    re (i, 0, ul) {
        ll s = 0;
        re (j, 0, nl)
            if ((i >> j) & 1)
                s += a[j];
        f[s] = i;
    }
    int ur = 1 << nr;
    re (i, 0, ur) {
        ll s = sum;
        re (j, 0, nr)
            if ((i >> j) & 1)
                s -= a[nl + j];
        if (f.count(s)) {
            int r = f[s];
            re (j, 0, nl)
                putchar('0' + (r >> j & 1));
            re (j, 0, nr)
                putchar('0' + (i >> j & 1));
            putchar('\n');
            return 0;
        }
    }
}