#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define lson now<<1
#define rson now<<1|1
using namespace std;
const int maxn=100009;


int n;
int c[maxn],h[maxn],a[maxn];

int p[maxn];

struct SegmentTree{
    int l,r;
    long long cnt,sum;
}tree[200<<2];
void pushup(int now){
    tree[now].cnt=tree[lson].cnt+tree[rson].cnt;
    tree[now].sum=tree[lson].sum+tree[rson].sum;
}
void build(int now,int l,int r){
    tree[now].l=l;tree[now].r=r;
    tree[now].cnt=tree[now].sum=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
}
void update(int now,int x,long long t1,long long t2){
    if(tree[now].l==tree[now].r){
        tree[now].cnt+=t1;
        tree[now].sum+=t2;
        return;
    }
    int mid=(tree[now].l+tree[now].r)>>1;
    if(x<=mid)update(lson,x,t1,t2);
    if(x>mid)update(rson,x,t1,t2);
    pushup(now);
}
long long query(int now,long long t){
    if(tree[now].l==tree[now].r){
        return 1LL*t*tree[now].l;
    }
    if(tree[lson].cnt>=t){
        return query(lson,t);
    }else{
        return query(rson,t-tree[lson].cnt)+tree[lson].sum;
    }
}
int cmp(int t1,int t2){
    return h[t1]<h[t2];
}

long long sum[maxn];

int main(){
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;++i)scanf("%d%d%d",&h[i],&c[i],&p[i]);
        build(1,1,200);
        for(int i=1;i<=n;++i){
            update(1,c[i],a[i],1LL*a[i]*c[i]);
        }
        
        for(int i=1;i<=n;++i)p[i]=i;
        sort(p+1,p+1+n,cmp);
        for(int i=1;i<=n;++i){
            sum[i]=sum[i-1]+a[p[i]];
        }
        
        long long now=0,ans=1000000000000000LL;
        int j;
        for(int i=n;i>=1;i=j-1){
            int x=p[i];
            long long cnth=0;
            update(1,c[x],-a[x],-1LL*a[x]*c[x]);
            cnth=a[x];
            
            cout<<"A"<<endl;
            while(j>1&&h[p[j-1]]==h[p[i]]){
                cout<<"B"<<endl;
                x=p[--j];cnth+=a[x];
                update(1,c[x],-a[x],-1LL*a[x]*c[x]);
            }
            
            cout<<"C"<<endl;
            
            if(sum[j-1]<=cnth){
                ans=min(ans,now);
            }else{
                ans=min(ans,query(1,sum[j-1]-cnth)+now);
            }
            
            cout<<"D"<<endl;
            for(int k=j;k<=i;++k)now=now+1LL*a[p[i]]*c[p[i]];
        }
        
        printf("%lld\n",ans);
    }
    
    return 0;
}
