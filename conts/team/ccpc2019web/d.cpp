#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
const int maxn=50009;

int Tn;

int n,m,Q;

int cntedge;
int head[maxn];
int to[maxn],nex[maxn],dist[maxn];
void Addedge(int x,int y,int z){
    nex[++cntedge]=head[x];
    to[cntedge]=y;
    dist[cntedge]=z;
    head[x]=cntedge;
}

struct Point{
    int x;long long d;
    Point(int xx,long long dd){
        x=xx;d=dd;
    }
    bool operator < (const Point &rhs) const{
        return d<rhs.d;
    }
};
std::multiset<Point>q;

int nn;
long long b[maxn];

int main(){
    scanf("%d",&Tn);
    while(Tn--){
        cntedge=nn=0;
        memset(head,0,sizeof(head));
        memset(nex,0,sizeof(nex));
        q.clear();
        
        scanf("%d%d%d",&n,&m,&Q);
        while(m--){
            int x,y,z;
            scanf("%d%d%d",&x,&y,&z);
            Addedge(x,y,z);
            q.insert(Point(y,z));
        }
        
        for(int i=1;i<=50000&&!q.empty();++i){
            Point now=*q.begin();
            q.erase(q.begin());
            
            b[++nn]=now.d;
            
            for(int j=head[now.x];j;j=nex[j]){
                q.insert(Point(to[j],now.d+dist[j]));
            }
            while (q.size() > 50000) {
                std::multiset<Point>::iterator it = q.end();
                q.erase(--it);
            }
        }
        
        while(Q--){
            int k;scanf("%d",&k);
            printf("%lld\n",b[k]);
        }
    }
    return 0;
}
