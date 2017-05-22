/*
POJ 1860
AC
图;最短路;SPFA;最长路
*/
#include <queue>
#include <cstdio>
using namespace std;
const int MAXN=110, MAXM=110*2;
int n, m;
int adj[MAXN];
int to[MAXM], enext[MAXM];
double rate[MAXN][MAXN], comm[MAXN][MAXN];
double d[MAXN]; // 到达某点处的最大持有

bool inque[MAXN];
int t;
double nv;
bool spfa(int s, double v) {
    queue<int> que;
    que.push(s);
    d[s]=v; // 最长路，d 初始化为 0
    while (!que.empty()) {
        t=que.front();
        que.pop();
        inque[t]=false;
        for (int e=adj[t]; e!=0; e=enext[e]) {
            nv=(d[t]-comm[t][to[e]])*rate[t][to[e]];
            if (d[to[e]]<nv) {
                d[to[e]]=nv;
                if (!inque[to[e]]) {
                    inque[to[e]]=true;
                    que.push(to[e]);
                }
            }
            if (d[s]>v) return true; // d[s] 可无限增长
        }
    }
    return false;
}

void add_edge(int no, int u, int v) {
    to[no]=v;
    enext[no]=adj[u];
    adj[u]=no;
}

int a, b;
double r1, c1, r2, c2;
int s;
double v;
int main() {
    scanf("%d%d%d%lf", &n, &m, &s, &v);
    for (int e=1; e<=m; ++e) {
        scanf("%d%d%lf%lf%lf%lf", &a, &b, &r1, &c1, &r2, &c2);
        add_edge(e, a, b);
        add_edge(m+e, b, a);
        rate[a][b]=r1;
        comm[a][b]=c1;
        rate[b][a]=r2;
        comm[b][a]=c2;
    }
    printf(spfa(s, v) ? "YES\n" : "NO\n");
    // printf("%lf", d[s]);
    return 0;
}
