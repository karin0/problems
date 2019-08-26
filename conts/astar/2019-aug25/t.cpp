#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int N=55;

typedef long long LL;

int D[N][N];
LL C[N][N];//Kirchhoff矩阵

LL Det(LL a[][N],int n)//生成树计数:Matrix-Tree定理
{
    LL ret=1;
    for(int i=1; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
            while(a[j][i])
            {
                LL t=a[i][i]/a[j][i];
                for(int k=i; k<n; k++)
                    a[i][k]=(a[i][k]-a[j][k]*t);
                for(int k=i; k<n; k++)
                    swap(a[i][k],a[j][k]);
                ret=-ret;
            }
        if(a[i][i]==0)
            return 0;
        ret=ret*a[i][i];
    }
    if(ret<0)
        ret=-ret;
    return ret;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        int n,m,k;
        scanf("%d%d%d",&n,&m,&k);
        memset(C,0,sizeof(C));
        memset(D,0,sizeof(D));
        int u,v;
        while(m--)
            {
            scanf("%d%d",&u,&v);
            u--;
            v--;
            ++D[u][v];
            ++D[v][u]=1;
        }
        for(int i=0; i<n; i++)
        {
            int u=0;
            for(int j=0; j<n; j++)
            {
                if(i!=j&&!D[i][j])
                {
                    u++;
                    C[i][j]=-1;
                }

            }
            C[i][i]=u;
        }
        LL res=Det(C,n);
        printf("%lld\n",res);
    }
    return 0;
}