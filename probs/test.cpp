#include<bits/stdc++.h>

#define maxn 200+5
#define maxm 40000+5
#define set(a,b) memset(a,(b),sizeof(a))
 
using namespace std;
 
typedef long long ll;
 
struct per{
  int a,b;
}s[maxn];
 
int f[maxn][maxm],sum[maxn];
int n,m,ans=INT_MAX;
 
bool comp(per a,per b)
{
  return a.b>b.b;
}
 
void DP()
{
  sort(s+1,s+n+1,comp);
  set(f,127/3);
  f[0][0]=0;
  for(int i=1;i<=n;i++)
    sum[i]=sum[i-1]+s[i].a;
  for(int i=1;i<=n;i++)
    for(int j=0;j<=sum[n];j++){
      if( j>=s[i].a )
    f[i][j]=min(f[i][j],max(f[i-1][j-s[i].a],j+s[i].b));
      if( sum[i]>=j )
    f[i][j]=min(f[i][j],max(f[i-1][sum[i]-j],j+s[i].b));
    }
  for(int i=0;i<=m;i++)
    ans=min(ans,f[n][i]);
}
 
int main()
{
  scanf("%d",&n);
  for(int i=1;i<=n;i++){
    scanf("%d%d",&s[i].a,&s[i].b);
    m+=s[i].a;
  }
  DP();
  printf("%d",ans);
  return 0;
}
