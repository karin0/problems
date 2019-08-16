#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=1e7+50;
const int mod=998244353;
typedef long long ll;
void add(int &a,int b){
    a+=b;
    if(a>=mod) a-=mod;
}
int dp[N],f[N],inv[N],sum[N];
void init(int d,int l){
    //cout<<d<<' '<<l<<endl;
    for(int i=0;i<d;i++) sum[i]=1,dp[i]=0;
    dp[0]=1;
    for(int i=d;i<=l;i++){
        dp[i]=sum[i-d];
        sum[i]=dp[i]+sum[i-1];
        if(sum[i]>=mod) sum[i]-=mod;
    }
    inv[0]=f[0]=f[1]=inv[1]=1;
    for(int i=2;i<=l;i++){
        f[i]=1LL*f[i-1]*i%mod;
        inv[i]=1LL*inv[mod%i]*(mod-mod/i)%mod;
    }
    for(int i=2;i<=l;i++) inv[i]=1LL*inv[i-1]*inv[i]%mod;
}
int cal(ll n,int m){
    if(n<0||m<0||n<m) return 0;
    return (1LL*f[n]*inv[m]%mod)*inv[n-m]%mod;
}
struct node{
    int t;
    int p;
    bool operator<(const node&a)const{
        return t<a.t;
    }
}a[3050];
int g[3050][2];
int main(){
    int d,l,m;
    scanf("%d%d%d",&l,&d,&m);
    init(d,l);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a[i].t,&a[i].p);
    }
    a[0].t=a[0].p=0;
    sort(a,a+m+1);
    g[0][1]=1;
    g[0][0]=0;
    for(int i=1;i<=m;i++){
        for(int j=0;j<i;j++){
            if(a[i].p>a[j].p&&a[i].t>a[j].t){
                int p=a[i].p-a[j].p;
                int t=a[i].t-a[j].t;
                add(g[i][0],1LL*g[j][1]*cal(1LL*p-1LL*d*t+t-1,t-1)%mod);
                add(g[i][1],1LL*g[j][0]*cal(1LL*p-1LL*d*t+t-1,t-1)%mod);
            }
        }
    }
    int res=dp[l];
    printf("res = %d\n", res);
    for(int i=1;i<=m;i++){
        int tmp=(g[i][1]-g[i][0]+mod)%mod;
        tmp=1LL*tmp*dp[l-a[i].p]%mod;
        add(res,tmp);
    }
    printf("%d\n",res);
}