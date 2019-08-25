#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int __=5e6;  //n^(2/3)项
#define mod (1000000007)
const int inv2  = ((mod+1)>>1);

bool pri[__+5];
int mu[__+5];
int num[__+5];

ll pw(ll a,int x){
    ll ret=1;
    for(;x;x>>=1,(a*=a)%=mod)if(x&1)(ret*=a)%=mod;
    return ret;
}

void mobius()
{
    mu[1]=1;
    pri[1]=true;
    for(int i=2;i<=__;i++)
    {
        if(!pri[i])
        {
            num[++num[0]]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=num[0]; ++j)
        {
            int p=num[j];
            ll v = i * p;
            if (v > __)
                break;
            pri[v]=true;
            if(!(i%p)){mu[v]=0;break;}
            mu[v]=-mu[i];
        }
    }
    for (int i = 2; i <= __; ++i) {
        mu[i] = (mu[i - 1] + mu[i] * (ll)i) %mod;
        if (mu[i] < 0)
            mu[i] += mod;
    }
}
#define myll ll
//unordered_
map<int, int> dp;

int cal(int x)
{
    if(x<=__)return mu[x];
    if(dp[x])return dp[x];
    myll res=1;
    for(int l=2,r;l<=x;l=r+1)
    {
        int t = x / l;
        r=x/t;
        res=(res-((ll)(l+r)*(r-l+1)>>1) %mod*cal(t))%mod;//(r-l+1)
        if (res < 0)
            res += mod;
    }
    return dp[x]=res;
}

int inv3=pw(3,mod-2);

myll get(myll a){
    a %= mod;
    ll t = a + a + 1;
    while (t >= mod)
        t -= mod;
    myll x=((a*(a+1))>>1)%mod*t%mod*inv3%mod;
    myll y=((a*(a+1))>>1)  %mod;
    return (x>y?x-y:y-x)*inv2 %mod;
}

int main(){
    mobius();
    //check();
    int T;// = 10000;
    scanf("%d",&T) ;
    while(T--) {
        int n,a,b;
        scanf("%d%d%d",&n,&a,&b);
        // n = T;
        cal(n);
        int ans=0;
        for(int l=1,r;l<=n;l=r+1)
        {
            int t = n / l;
            r=n/t;
            ans=(ans+get(t)*(cal(r)-(l==1?0:(cal(l-1)))))%mod;// )%=mod;//(r-l+1)
            if (ans<0)
                ans += mod;
        }
        printf("%d\n",ans);
        //cout<<ans<<endl;
        // dp.clear();
    }
}