/*
HDU 2544
AC
模板;最短路;单源最短路;SPFA;邻接表
15ms;1536K
*/
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int INF=0x3f3f3f3f; // 允许自加一次
int n, m;
int to[10010], cost[10010], enext[10010];
int adj[110];
int d[110];
// int prev[110];

bool inque[110];
int cur;
// int cnt[10010];
bool spfa(int s) {
    queue<int> que; // 置空
    memset(inque, 0, sizeof(inque));
    // memset(cnt, 0, sizeof(cnt));
    memset(d, INF, sizeof(d));
    d[s]=0;
    que.push(s);
    // inque[s]=true;
    while (!que.empty()) {
        cur=que.front(); // 队首，栈顶
        que.pop();
        inque[cur]=false;
        for (int e=adj[cur]; e!=0; e=enext[e]) {
            if (d[to[e]]>d[cur]+cost[e]) {
                d[to[e]]=d[cur]+cost[e];
                if (!inque[to[e]]) {
                    que.push(to[e]);
                    inque[to[e]]=true;
                    //if (++cnt[to[e]]>n) return false; // 负环
                }
            }
        }
    }
    return true;
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
        spfa(1); // 单源
        printf("%d\n", d[n]);
    }
    return 0;
}
