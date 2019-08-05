
#include<bits/stdc++.h>
#define debug(x) cout<<#x<<"="<<x<<endl
using namespace std;
const int N = 109;

struct node{int x,y,sta,step;};
struct chess{int x,y,opt;}a[N];
bool vis[N][N][1<<14],atk[1<<14][N][N],base[N][N];
int hz[8]={-2,-1,1,2,2,1,-1,-2},sz[8]={1,2,2,1,-1,-2,-2,-1};
int Hz[8]={-1,-1,-1,0,1,1,1,0},Sz[8]={-1,0,1,1,1,0,-1,-1};
int idx[N][N];
int n,h,s,ht,st,tot,mr;
char str[N];

// 1: queen
// 2: castle
// 3: bishop
// 4: soldier

void ClearLove()
{
    tot=0;
    memset(vis,0,sizeof vis);
    memset(atk,0,sizeof atk);
    memset(base,0,sizeof base);
    memset(idx,0,sizeof idx);
}

int main()
{
    while(~scanf("%d",&n))
    {
        ClearLove();
        for(int i=1;i<=n;i++)
        {
            scanf("%s",str+1);
            for(int j=1;j<=n;j++)
            {
                if(str[j]=='X')
                {
                    ht=i;st=j;
                    for(int k=0;k<8;k++)
                    {
                        int hh=i+Hz[k],ss=j+Sz[k];
                        if(hh>=1&&hh<=n&&ss>=1&&ss<=n) base[hh][ss]=1;
                    }
                    idx[i][j]=tot;
                }
                if(str[j]=='Q') a[++tot]=(chess){i,j,1},idx[i][j]=tot;
                if(str[j]=='C') a[++tot]=(chess){i,j,2},idx[i][j]=tot;
                if(str[j]=='B') a[++tot]=(chess){i,j,3},idx[i][j]=tot;
                if(str[j]=='P') a[++tot]=(chess){i,j,4},idx[i][j]=tot;
                if(str[j]=='K')
                    for(int k=0;k<8;k++)
                    {
                        int hh=i+hz[k],ss=j+sz[k];
                        if(hh>=1&&hh<=n&&ss>=1&&ss<=n) base[hh][ss]=1;
                    }
                if(str[j]=='O') h=i,s=j;
            }
        }
        mr=(1<<tot)-1;
        for(int i=0;i<=mr;i++)
        {
            memcpy(atk[i],base,sizeof base);
            for(int j=1;j<=tot;j++) if(i&(1<<j>>1))
            {
                int x=a[j].x,y=a[j].y;
                if(a[j].opt==1)
                {
                    for(int k=1;k<=n;k++) if(k!=y) atk[i][x][k]=1;
                    for(int k=1;k<=n;k++) if(k!=x) atk[i][k][y]=1;
                    for(int hh=x+1,ss=y+1;hh<=n&&ss<=n;hh++,ss++) atk[i][hh][ss]=1;
                    for(int hh=x-1,ss=y-1;hh>=1&&ss>=1;hh--,ss--) atk[i][hh][ss]=1;
                    for(int hh=x+1,ss=y-1;hh<=n&&ss>=1;hh++,ss--) atk[i][hh][ss]=1;
                    for(int hh=x-1,ss=y+1;hh>=1&&ss<=n;hh--,ss++) atk[i][hh][ss]=1;
                }
                if(a[j].opt==2)
                {
                    for(int k=1;k<=n;k++) if(k!=y) atk[i][x][k]=1;
                    for(int k=1;k<=n;k++) if(k!=x) atk[i][k][y]=1;
                }
                if(a[j].opt==3)
                {
                    for(int hh=x+1,ss=y+1;hh<=n&&ss<=n;hh++,ss++) atk[i][hh][ss]=1;
                    for(int hh=x-1,ss=y-1;hh>=1&&ss>=1;hh--,ss--) atk[i][hh][ss]=1;
                    for(int hh=x+1,ss=y-1;hh<=n&&ss>=1;hh++,ss--) atk[i][hh][ss]=1;
                    for(int hh=x-1,ss=y+1;hh>=1&&ss<=n;hh--,ss++) atk[i][hh][ss]=1;
                }
                if(a[j].opt==4)
                {
                    if(x+1<=n&&y-1>=1) atk[i][x+1][y-1]=1;
                    if(x+1<=n&&y+1<=n) atk[i][x+1][y+1]=1;
                }
            }
        }
        if(atk[mr][h][s])
        {
            puts("-1");
            continue;
        }
        queue<node> q;
        q.push((node){h,s,mr,0});
        vis[h][s][mr]=1;
        bool flag=0;
        while(!q.empty())
        {
            int x=q.front().x,y=q.front().y,sta=q.front().sta,step=q.front().step;q.pop();
            for(int i=0;i<8;i++)
            {
                int hh=x+hz[i],ss=y+sz[i],nxt=sta;
                if(hh<1||hh>n||ss<1||ss>n) continue;
                if(hh==ht&&ss==st)
                {
                    flag=1;
                    printf("%d\n",step+1);
                    break;
                }
                if(atk[sta][hh][ss]) continue;
                if(idx[hh][ss]&&(sta&(1<<idx[hh][ss]>>1))) nxt-=(1<<idx[hh][ss]>>1);
                if(vis[hh][ss][nxt]) continue;
                vis[hh][ss][nxt]=1;
                q.push((node){hh,ss,nxt,step+1});
            }
            if(flag) break;
        }
        if(!flag) puts("-1");
    }
    return 0;
}
