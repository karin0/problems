#include <cstdio>
#include <cmath>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef long long ll;

const int N = 200002;

int a[N];
ll s[N];
int main() {
    int n, m, mx = 0;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        scanf("%d", &a[i]);
        s[i] = s[i - 1] + a[i];
        mx = std::max(mx, a[i]);
    }

    // printf("mx = %d\n", mx);
    while (m--) {
        int l, r, x, y;
        scanf("%d%d%d%d", &l, &r, &x, &y);
        long double t = (long double)(s[r] - s[l - 1]) * x / y, al = 0, ar = mx, amid;
        // printf("t = %f\n", t);
        int lll = 50;
        while (lll--) {
            // printf("(%f, %f)\n", al, ar);
            amid = (al + ar) / 2.0;

            long double sss = 0;
            rep (i, l, r)
                if (a[i] > amid)
                    sss += a[i] - amid;
            // printf("(%f, %f), mid=%f, truemid=%d, tc=%d, ts=%lld, sss = %f\n", al, ar, amid, tm, tc,ts,sss);
            // printf("ts = %f\n", ts);
            if (sss < t)
                ar = amid;
            else if (sss > t)
                al = amid;
            else
                break;
        }
        printf("%.15f\n", (double)amid);
    }
}