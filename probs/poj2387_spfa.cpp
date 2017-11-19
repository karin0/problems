/*
POJ 2387

图;最短路;SPFA
*/
#include <queue>
#include <cstring>
#include <cstdio>
using namespace std;

const int MAXN=1010, MAXM=2010*2, INF=0x3f3f3f3f;
int n, m;
int adj[MAXN], d[MAXN]; // 1 .. n
int to[MAXM], cost[MAXM], enext[MAXM]; // 1 .. m

bool inque[MAXN];
int t;
void spfa(int s) {
    queue<int> q;
    memset(d, INF, sizeof(d));
    memset(inque, false, sizeof(inque));
    d[s]=0;
    q.push(s);
    while (!q.empty()) {
        t=q.front();
        q.pop();
        inque[t]=false;
        for (int e=adj[t]; e!=0; e=enext[e]) {
            if (d[to[e]]>d[t]+cost[e]) {
                d[to[e]]=d[t]+cost[e];
                if (!inque[to[e]]) {
                    q.push(to[e]);
                    inque[to[e]]=true;
                }
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
    spfa(1);
    printf("%d", d[n]); // from 1 to n
    return 0;
}
