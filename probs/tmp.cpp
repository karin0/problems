#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL;
const int N = 100050;
 
int c[4], d[4], tot, s;
LL ans, f[N];
 
void calc(int i,int k,int sum)
{
    if(sum < 0) return;
    if(i == 4)
    {
        if(k&1) ans -= f[sum];
        else ans += f[sum];
        return;
    }
    calc(i+1,k+1,sum-(d[i]+1)*c[i]);
    calc(i+1,k,sum);
}
 
int main()
{
    int i, j;
    scanf("%d%d%d%d%d",&c[0],&c[1],&c[2],&c[3],&tot);
    f[0] = 1;
    for(i = 0; i <= 3; ++ i)
        for(j = c[i]; j <= N - 50; ++ j)
            f[j] += f[j-c[i]];
    for(j = 0; j <= 50; ++ j)
        printf("f[%d] = %lld\n", j, f[j]);
    while(tot--)
    {
        scanf("%d%d%d%d%d",&d[0],&d[1],&d[2],&d[3],&s);
        ans = 0;
        calc(0,0,s);
        printf("%lld\n",ans);
    }
    return 0;
}
