#include <cstdio>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

const int N = 3003;
char a[N][N];
int h[N];

int s[N], ss[N], sss[N];
int prev[N], s4[N];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    long long ans = 0;

    rep (i, 1, n)
        scanf("%s", a[i] + 1);
    rep (i, 1, n) {
        int z = 0;
        int sn = 0;

        int s4n = 0;
        rep (j, 1, m) {
            if (a[i][j] == '1')
                h[j] += 1;
            else
                h[j] = 0;

            while (s4n && h[s4[s4n]] >= h[j])
                --s4n;
            prev[j] = s4n ? s4[s4n] : 0;
            s4[++s4n] = j;
        }

        rep (j, 1, m) {
            if (a[i + 1][j] != '1')
                z = j;
            if (a[i][j] == '1') {
                int t = j;
                while (sn > 0) {
                    if (ss[sn] > h[t])
                        --sn;
                    else if (ss[sn] == h[t])
                        t = s[sn], --sn;
                    else
                        break;
                }
                int r = h[t];
                s[++sn] = t;
                ss[sn] = r;
                sss[sn] = prev[t] + 1;

                if (h[j] > h[j + 1]) {
                    int p = std::upper_bound(ss + 1, ss + sn + 1, h[j + 1]) - ss;
                    int q = std::upper_bound(sss + 1, sss + sn + 1, z) - sss - 1;
                    /*rep (k, 1, sn)
                        printf("sta[%d] = %d, %d, %d\n", k, s[k], ss[k], sss[k]);
                    printf("%d, (%d, %d), [%d ->  %d, %d]\n", z, i, j, p, q, sn);*/
                    if (p <= sn && p <= q) {
                        //printf("Got %d\n", q-p+1);
                        ans += q - p + 1;
                    }

                }/* else 
                    rep (k, 1, sn)
                        printf("(%d, %d)  sta[%d] = %d, %d\n", i,j,k, s[k], ss[k]);

                if (h[j - 1] < h[j] && h[j + 1] < h[j] && z == j)
                    ++ans, printf("AAA %d\n", j);*/
            } else
                sn = 0;
        }
    }
    printf("%lld\n", ans);

    return 0;
}