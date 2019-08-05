/*
POJ 2387
AC
图;最短路;Dijkstra;优先队列
32ms;648K
*/
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN=1010, MAXM=2010*2, INF=0x3f3f3f3f; // 边数 * 2 !!
int n, m;
int adj[MAXN], d[MAXN]; // 1 .. n
int to[MAXM], cost[MAXM], enext[MAXM]; // 1 .. m

typedef pair<int, int> P; // dist, no
int t;
void dijk(int s) {
    priority_queue<P, vector<P>, greater<P> > pq;
    memset(d, INF, sizeof(d));
    d[s]=0;
    pq.push(P(0, s));
    while (!pq.empty()) {
        t=pq.top().second;
        pq.pop();
        for (int e=adj[t]; e!=0; e=enext[e]) {
            if (d[to[e]]>d[t]+cost[e]) {
                d[to[e]]=d[t]+cost[e];
                pq.push(P(d[to[e]], to[e]));
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

int u, v, w;
int main() {
    scanf("%d%d", &m, &n);
    for (int e=1; e<=m; e++) {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(e, u, v, w);
        add_edge(m+e, v, u, w);
    }
    dijk(1);
    printf("%d", d[n]); // from 1 to n
    return 0;
}
