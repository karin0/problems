#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=400009;
const int inf=1000000009;

int n,m;
int ans;
int ui[maxn],vi[maxn],li[maxn],ri[maxn];

int ch[maxn][2],fa[maxn],mi[maxn],mie[maxn],ky[maxn],rev[maxn];
int son(int x){
    if(ch[fa[x]][0]==x)return 0;
    else return 1;
}
int isroot(int x){
    return (ch[fa[x]][0]!=x)&&(ch[fa[x]][1]!=x);
}

void pushup(int x){
    mi[x]=ky[x];mie[x]=x-n;
    if(mi[ch[x][0]]<mi[x]){
        mi[x]=mi[ch[x][0]];
        mie[x]=mie[ch[x][0]];
    }
    if(mi[ch[x][1]]<mi[x]){
        mi[x]=mi[ch[x][1]];
        mie[x]=mie[ch[x][1]];
    }
}
void pushdown(int x){
    if(rev[x]){
        rev[ch[x][0]]^=1;
        rev[ch[x][1]]^=1;
        rev[x]^=1;
        swap(ch[x][0],ch[x][1]);
    }
}
void down(int x){
    if(!isroot(x))down(fa[x]);
    pushdown(x);
}

void Rotate(int x){
    int y=fa[x],z=fa[y];
    int b=son(x),c=son(y);
    int a=ch[x][b^1];
    if(!isroot(y))ch[z][c]=x;
    fa[x]=z;
    if(a)fa[a]=y;
    ch[y][b]=a;
    fa[y]=x;ch[x][b^1]=y;
    pushup(y);pushup(x);
}

void Splay(int x){
    down(x);
    while(!isroot(x)){
        int y=fa[x];
        if(isroot(y)){
            Rotate(x);
        }else{
            if(son(x)==son(y))Rotate(y);
            else Rotate(x);
            Rotate(x);
        }
    }
}

void Access(int x){
    for(int t=0;x;t=x,x=fa[x]){
        Splay(x);
        ch[x][1]=t;
        pushup(x);
    }
}
int find(int x){
    Access(x);Splay(x);
    for(;;){
        pushdown(x);
        if(ch[x][0])x=ch[x][0];
        else return x;
    }
}
void Makeroot(int x){
    Access(x);Splay(x);rev[x]^=1;
}
void Link(int x,int y){
    Makeroot(x);fa[x]=y;
    
}
void Cut(int x,int y){
    Makeroot(x);Access(y);Splay(y);
    fa[ch[y][0]]=0;ch[y][0]=0;pushup(y);
}
int query(int x,int y){
    Makeroot(x);Access(y);Splay(y);
    return mie[y];
}

int read(){
    int r=0,k=1;
    char c=getchar();
    for(;c<'0'||c>'9';c=getchar())if(c=='-')k=-1;
    for(;c>='0'&&c<='9';c=getchar())r=r*10+c-'0';
    return r*k;
}

int b[maxn],nn;
vector<int>G[maxn];

void del(int e){
    int u=ui[e],v=vi[e];
    if(find(u)!=find(v))return;
    Cut(u,e+n);Cut(v,e+n);
}

void ins(int e){
    int u=ui[e],v=vi[e];
    if(find(u)!=find(v)){
        Link(u,e+n);
        Link(v,e+n);
    }else{
        del(query(u,v));
        Link(u,e+n);
        Link(v,e+n);
    }
}

int main(){
    mi[0]=ky[0]=inf;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;++i){
        ui[i]=read();vi[i]=read();
        li[i]=read();ri[i]=read();
        b[++nn]=li[i];
        b[++nn]=ri[i]+1;
    }
    sort(b+1,b+1+nn);
    nn=unique(b+1,b+1+nn)-b-1;
    for(int i=1;i<=n;++i){
        int p;
        p=lower_bound(b+1,b+1+nn,li[i])-b;
        G[p].push_back(i);
        p=lower_bound(b+1,b+1+nn,ri[i]+1)-b;
        G[p].push_back(i);
    }
    
    for(int i=1;i<=n;++i)mi[i]=ky[i]=inf;
    for(int i=n+1;i<=n+m;++i){
        mi[i]=ky[i]=ri[i-n];mie[i]=i-n;
    }
    
    for(int t=1;t<=nn-1;++t){
        for(int i=0;i<G[t].size();++i){
            int e=G[t][i];
            if(li[e]==b[t]){
                ins(e);
            }else{
                del(e);
            }
        }
        if(find(1)==find(n))ans+=(b[t+1]-b[t]);
    }
    
    printf("%d\n",ans);
    
    return 0;
}
