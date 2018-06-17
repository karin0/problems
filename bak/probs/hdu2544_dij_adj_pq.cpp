/*
HDU 2544
AC
模板;最短路;单源最短路;Dijkstra;优先队列;堆;邻接表
15ms;1540K
*/
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int INF=1000000000;
int n, m;
int to[10010], cost[10010], enext[10010];
int adj[110];
int d[110];
// int prev[110];

int nv;
typedef pair<int, int> P; // first 为距离，second 为顶点序号，按 first 排序
P tmp;
void dijk(int s) {
    priority_queue<P, vector<P>, greater<P> > que; // 变大的优先队列
    for (int i=1; i<=n; i++) {
        d[i]=INF;
    }
    d[s]=0; // 保证初次使用的是源点 s
    que.push(P(0, s));
    while (!que.empty()) {
        tmp=que.top();
        que.pop();
        nv=tmp.second;
        // 使用 nv 松弛以 nv 为起点的所有边
        for (int i=adj[nv]; i!=0; i=enext[i]) {
            if (d[nv]+cost[i]<d[to[i]]) {
                d[to[i]]=d[nv]+cost[i];
                que.push(P(d[to[i]], to[i])); // 距离被更新后再入队
                // prev[i]=nv;
            }   
        }
    }
}

void add_edge(int no, int u, int v, int w) {
    to[no]=v;
    cost[no]=w;
    enext[no]=adj[u];
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
