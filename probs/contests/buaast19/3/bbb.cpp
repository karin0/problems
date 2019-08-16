#include <cstdio>
#include <algorithm>
#include<iostream>
#include<cstring>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)

const int N = 3003;
char a[N][N];
int h[N];

int s[N], ss[N];
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    long long ans = 0;

    rep (i, 1, n)
        scanf("%s", a[i] + 1);
    rep (i, 1, n) {
        int z = 0;
        int sn = 0;

        rep (j, 1, m) {
            if (a[i][j] == '1')
                h[j] += 1;
            else
                h[j] = 0;
        }

        int pre=0;
        rep (j, 1, m) {
            if (a[i + 1][j] != '1'){
                z=j;
            }
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
                s[++sn] = t;
                ss[sn] = h[t];
                int p = std::upper_bound(ss + 1, ss + sn + 1, h[j + 1]) - ss;
                int q = std::upper_bound(s + 1, s + sn + 1, z) - s - 1;
                /*
                rep (i, 1, sn)
                    printf("sta[%d] = %d, %d\n", i, s[i], ss[i]);
                printf("%d, (%d, %d), [%d ->  %d, %d]\n", z, i, j, p, q, sn);
                */
                
                
                if(q){
                    if(s[q]<z&&q<sn)++q;
                }else{
                    if(pre<z&&q<sn)++q;
                }
                
                if (p <= sn && p <= q) {
                    // printf("Got %d\n", q-p+1);
                    ans += std::max(0, q - p + 1);
                }
                
//                if(z>pre&&z<s[1]&&ss[1]>h[j+1]){
//                  ++ans;
//                  if(i==4&&j==5)printf("%d\n",std::max(0,q-p+1)+1);
//              }else{
//                  if(i==4&&j==5)printf("%d\n",std::max(0,q-p+1));
//              }
                
            } else{
                pre=j;
                sn = 0;
            }
        }
    }
    printf("%lld\n", ans);

    return 0;
}