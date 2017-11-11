#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int MAXN = 10005, MAXM = 200005, INF = 0x7f7f7f7f;
int n, m, s, t, ecnt;
struct Edge {
    int v;
    Edge *next;
} se[MAXM << 1], *adj[MAXN], *radj[MAXN];
inline void arc(int u, int v) {
    Edge &e = se[++ecnt];
    e.v = v;
    e.next = adj[u];
    adj[u] = &e;
}
inline void rarc(int u, int v) {
    Edge &e = se[++ecnt];
    e.v = v;
    e.next = radj[u];
    radj[u] = &e;
}
bool bad[MAXN], rec[MAXN]; // *** they are different!!
void bfs0() {
    static std::queue<int> que;
    static int u, v;
    que.push(t);
    rec[t] = true;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        for (Edge *e = radj[u]; e; e = e->next) {
            v = e->v;
            if (!rec[v]) {
                rec[v] = true; // do this before pushing is good;
                que.push(v);
            }
        }
    }
    for (u = 1; u <= n; ++u) {
        if (rec[u]) {
            for (Edge *e = adj[u]; e; e = e->next) {
                if (!rec[e->v]) {
                    bad[u] = true;
                    break;
                }
            }
        }
    }
}
int bfs() {
    static std::queue<int> que;
    static int d[MAXN], u, v;
    if (bad[s] || !rec[s])
        return INF;
    memset(d, 0x7f, sizeof(int) * (n + 2));
    d[s] = 0;
    que.push(s);
    while (!que.empty()) {
        u = que.front();
        que.pop();
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v; // ***
            if (d[v] == INF && rec[v] && !bad[v]) { // *** not d[v]
                d[v] = d[u] + 1;
                if (v == t)
                    return d[t];
                que.push(v);
            }
        }
    }
    return INF;
}

int main() {
    static int i, u, v, ret;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        arc(u, v);
        rarc(v, u);
    }
    scanf("%d%d", &s, &t);
    bfs0();
    ret = bfs();
    printf("%d\n", ret >= INF ? -1 : ret);
    return 0;
}
