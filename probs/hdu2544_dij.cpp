/*
HDU 2544
AC
模板;最短路;单源最短路;Dijkstra;邻接矩阵
15ms;1456K
*/
#include <cstdio>
using namespace std;

const int INF=1000000000;
int n, m;
int cost[110][110]; // 邻接矩阵
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
        for (int i=1; i<=n; i++) {
            if (d[nv]+cost[nv][i]<d[i]) {
                d[i]=d[nv]+cost[nv][i];
                // prev[i]=nv;
            }
        }
    }
}
int main() {
    int u, v, w, half_m;
    while (true) {
        scanf("%d%d", &n, &half_m);
        if (n==0 && half_m==0) break;
        m=2*half_m;
        // 无向图，两点建两条有向边
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                cost[i][j]=INF;
            }
        }
        for (int i=0; i<half_m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            cost[u][v]=w;
            cost[v][u]=w;
        }
        dijk(1); // 单源
        printf("%d\n", d[n]);
    }
    return 0;
}
