/*
hihoCoder 1121

图;DFS;搜索;二分图;二分图判定
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN=10010, MAXM=40010 * 2;
int n, m;
int adj[MAXN]; // 1 .. n
int status[MAXN]; // 0 - never visited, 1, 2
int to[MAXM], enext[MAXM]; // 1 .. m

int v;
inline int opp(int stat) {
    return stat-1 ? 1 : 2;
}

bool dfs(int s, int stat) {
    status[s]=stat;
    for (int e=adj[s]; e!=0; e=enext[e]) {
        v=to[e];
        if (status[v]) {
            if (status[v]==stat)
                return false;
        } else 
            if (!dfs(v, opp(stat)))
                return false; // 这里也要返回
    }
    return true;
}

void add_edge(int no, int u, int v) {
    to[no]=v;
    enext[no]=adj[u];
    adj[u]=no;
}

int t, u;
// int v;
int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);
        memset(adj, 0, sizeof(adj));
        memset(status, 0, sizeof(status));
        memset(to, 0, sizeof(to));
        memset(enext, 0, sizeof(enext));
        for (int e=1; e<=m; e++) {
            scanf("%d%d", &u, &v);
            add_edge(e, u, v);
            add_edge(m+e, v, u); // 无向边
        }
        // m+=m;
        for (int u=1; u<=n; u++) {
            if (!status[u] && !dfs(u, 1)) {
                printf("Wrong\n");
                goto _out;
            }    
        }
        printf("Correct\n");
        _out:; // 冒号
    }
    return 0;
}
