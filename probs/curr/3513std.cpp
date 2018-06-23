#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define N 500003
#define pi acos(-1)
#define LL long long 
using namespace std;
struct data{
    double x,y;
    data(double X=0,double Y=0){
        x=X,y=Y;
    }
}f[N];
data operator +(data a,data b){
    return data(a.x+b.x,a.y+b.y);
}
data operator -(data a,data b){
    return data(a.x-b.x,a.y-b.y);
}
data operator *(data a,data b)
{
    return data(a.x*b.x-a.y*b.y,a.y*b.x+a.x*b.y);
}
int n,T,a[N],L,R[N],n1;
LL g[N],t[N];
void FFT(data a[],int n,int opt)
{
    for (int i=0;i<n;i++)
        if (i>R[i]) swap(a[i],a[R[i]]);
    for (int i=1;i<n;i<<=1) {
        data wn=data(cos(pi/i),opt*sin(pi/i));
        for (int p=i<<1,j=0;j<n;j+=p) {
            data w=data(1,0);
            for (int k=0;k<i;k++,w=w*wn) {
                data x=a[j+k],y=w*a[j+k+i];
                a[j+k]=x+y; a[j+k+i]=x-y;
            }
        }
    }
    if (opt==-1)  for (int i=  0;i<n;i++) f[i].x/=n;
}
int main()
{
    scanf("%d",&T);
    while (T--){
        scanf("%d",&n); int mx=0; LL sum=n;
        memset(a,0,sizeof(a));
        memset(g,0,sizeof(g));
        memset(f,0,sizeof(f));
        memset(t,0,sizeof(t));
        for (int i=1;i<=n;i++) {
            scanf("%d",&a[i]); mx=max(mx,a[i]);
            g[a[i]*2]--; ++f[a[i]].x; t[a[i]]++;
        }
        for (int i=mx;i>=1;i--) t[i]+=t[i+1];
        mx*=2; L=0; sum=sum*(LL)(n-1)*(LL)(n-2)/6;
        for (n1=1;n1<=mx;n1<<=1) L++;
        for (int i=0;i<=n1;i++) R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
        FFT(f,n1,1);
        for (int i=0;i<=n1;i++) f[i]=f[i]*f[i];
        FFT(f,n1,-1);
        for (int i=0;i<=n1;i++) g[i]+=(LL)(f[i].x+0.5);
        LL ans=0;
        for (int i=0;i<=n1;i++) ans+=(g[i]/2)*t[i]; 
        ans=sum-ans;
        printf("%.7lf\n",(double)ans*1.0/sum);
    }
}
