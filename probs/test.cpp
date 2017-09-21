#include<bits/stdc++.h>
int n,s,ans;
inline int read()
{
    int an=0;
    char ch=' ';
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9'){
        an=an*10+ch-'0';
        ch=getchar();
    }
    return an;
}
const int maxn=100005;
struct edge{
    int v,nxt;
}g[maxn];
int cnt,a[maxn],f[maxn][1005],head[maxn],root,fa[maxn];
int qu[maxn<<3];
inline void add_edge(int qwq,int b)
{
    g[++cnt]=(edge){b,head[qwq]};
    fa[b]=qwq;
    head[qwq]=cnt;
}
int r = 1;
void dfs1(int now,int tmpa,int l)
{
    if(a[now]<=s){
        tmpa+=a[now];
        qu[r++]=now;
    }
    if(tmpa>s){
        while(tmpa>s&&l<r){
            tmpa-=a[qu[l++]];
        }
    }
    if(tmpa==s){
        ans++,tmpa-=a[qu[l++]];
    }
    for(int i=head[now];i;i=g[i].nxt){
        dfs1(g[i].v,tmpa,l);
    }
    if(a[now]<=s)
        qu[--r]=0;
}
int main()
{
    scanf("%d%d",&n,&s);
    for(int i=1;i<=n;++i){
        a[i]=read();
    }
    for(int i=1;i<n;++i){
        int u=read();
        int v=read();
        add_edge(u,v);
    }
//    for(int i=1;i<=n;++i){
//        if(!fa[i]){
//            root=i;break;
//        }
//    }
    dfs1(1,a[1],1);
    printf("%d",ans);
    return 0;
}
