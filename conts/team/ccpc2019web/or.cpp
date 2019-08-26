#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int __=5;  //n^(2/3)项
#define mod (1000000007)
#define inv2 ((mod+1)/2)

bool pri[__+5];
int mu[__+5],num[__+5];
int sum[__+5];

ll Mod(ll x){
    x%=mod;
    if(x<0)x+=mod;
    return x;
}

ll pw(ll a,int x){
    ll ret=1;
    for(;x;x>>=1,(a*=a)%=mod)if(x&1)(ret*=a)%=mod;
    return ret;
}

void mobius()
{
    mu[1]=sum[1]=1;
    pri[1]=true;
    for(int i=2;i<=__;i++)
    {
        if(!pri[i])
        {
            num[++num[0]]=i;
            mu[i]=-1;
        }
        for(int j=1;j<=num[0] && i*num[j]<=__;++j)
        {
            int &p=num[j];
            pri[i*p]=true;
            if(!(i%p)){mu[i*p]=0;break;}
            mu[i*p]=-mu[i];
        }
        sum[i]=Mod(sum[i-1]+mu[i]*i);
    }
}
#define myll ll
//unordered_
map<ll,myll>dp;

ll cal(ll x)
{
    if(x<=__)return sum[x];
    if(dp[x])return dp[x];
    myll res=1;
    for(ll l=2,r;l<=x;l=r+1)
    {
        r=x/(x/l);
        res-=(l+r)*(r-l+1)/2 %mod*cal(x/l)%mod;//(r-l+1)
        res=Mod(res);
    }
    return dp[x]=res;
}

void check(){
    for(int i=1;i<1000;i++)cal(i);
    cout<<dp.size()<<endl;
    for(auto x:dp){
        if(x.first>=__)continue;
        cout<<x.first<<endl;
        if(sum[x.first]!=x.second){
            cout<<x.first<<' '<<sum[x.first]<<' '<<(ll)x.second<<endl;
        }
    }
}

int inv3=pw(3,mod-2);

myll get(myll a){
    myll x=(__int128)a*(a+1)/2*(2*a+1)/3%mod;
    myll y=a*(a+1)/2  %mod;
    return (x>y?x-y:y-x)*inv2 %mod;
}

int main(){
    mobius();
    //check();
    int T;// = 10000;
    scanf("%d",&T) ;
    while(T--){
        int n,a,b;
        scanf("%d%d%d",&n,&a,&b);
        //n = T;
        cal(n);
        int ans=0;
        for(ll l=1,r;l<=n;l=r+1)
        {
            r=n/(n/l);
            ans+=get(n/l)*(cal(r)-(l==1?0:(cal(l-1))))%mod;// )%=mod;//(r-l+1)
            ans=Mod(ans);
        }
        printf("%d\n",ans);
        //cout<<ans<<endl;
        dp.clear();
    }
    return 0;
}