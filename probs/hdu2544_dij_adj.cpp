/*
HDU 2544
AC
模板;最短路;单源最短路;Dijkstra;邻接表
15ms;1484K
*/
#include <cstring>
#include <cstdio>
using namespace std;

const int INF=1000000000;
int n, m;
int to[10010], cost[10010], next[10010];
int adj[110];
int d[110];
// int prev[110];

bool used[110];
int nv;
void dijk(int s) {
    for (int i=1; i<=n; i++) {
        d[i]=INF;
        used[i]=false;
    }
    d[s]=0; // 保证初次使用的是源点 s
    while (true) {
        nv=-1;
        for (int i=1; i<=n; i++) {
            if (!used[i] && (nv==-1 || d[i]<d[nv])) nv = i;
        } // 查找到源点距离最小且未使用的顶点
        if (nv==-1) break; // 所有顶点都使用过了
        // 使用 nv 松弛以 nv 为起点的所有边
        used[nv]=true;
        for (int i=adj[nv]; i!=0; i=next[i]) {
            if (d[nv]+cost[i]<d[to[i]]) {
                d[to[i]]=d[nv]+cost[i];
                // prev[i]=nv;
            }   
        }
    }
}

void add_edge(int no, int u, int v, int w) {
    to[no]=v;
    cost[no]=w;
    next[no]=adj[u];
    adj[u]=no;
}

int main() {
    int u, v, w, half_m;
    while (true) {
        scanf("%d%d", &n, &half_m);
        if (n==0 && half_m==0) break;
        memset(adj, 0, sizeof(adj)); //  必须清空邻接表！
        m=2*half_m;
        // 无向图，两点建两条有向边
        for (int i=1; i<=half_m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            add_edge(i, u, v, w);
            add_edge(half_m+i, v, u, w);
        }
        dijk(1); // 单源
        printf("%d\n", d[n]);
    }
    return 0;
}
