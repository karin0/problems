/*
HDU 2544
AC
模板;最短路;单源最短路;Bellman-Ford;边目录
15ms;1488K
*/
#include <cstdio>
using namespace std;

const int INF=1000000000;
int n, m;
int from[10010], to[10010], cost[10010]; // 边目录
int d[110];

bool Bfond(int s) {
    bool ifUpdated;
    for (int i=1; i<=n; i++) {
        d[i]=INF;
    }
    d[s]=0;
    // int counter=0;
    while (true) {
        // counter++;
        // if (counter==n) return false; // 有负圈
        ifUpdated=false;
        for (int i=0; i<m; i++) { // 遍历所有边
            if (d[from[i]]!=INF && d[to[i]]>d[from[i]]+cost[i]) {
                d[to[i]]=d[from[i]]+cost[i];
                ifUpdated=true;
            }
        }
        if (!ifUpdated) break;
    }
    return true;
}
int main() {
    int u, v, w, half_m, nega_i;
    while (true) {
        scanf("%d%d", &n, &half_m);
        if (n==0 && half_m==0) break;
        m=2*half_m;
        // 无向图，两点建两条有向边
        for (int i=0; i<half_m; i++) {
            scanf("%d%d%d", &u, &v, &w);
            nega_i=half_m+i;
            from[i]=u;
            to[i]=v;
            cost[i]=w;
            from[nega_i]=v;
            to[nega_i]=u;
            cost[nega_i]=w;
        }
        Bfond(1); // 单源
        printf("%d\n", d[n]);
    }
    return 0;
}
