#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int MAXN = 5010, MAXM = 6010, INF = 0x3f3f3f3f;

int n, m, p, uni, adj[MAXN], to[MAXM], next[MAXM];
int req[MAXM], keys[MAXN];
inline void arc(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}
/*
struct State {
    int u, d, s;
};
inline bool operator < (const State &x, const State &y) {
    return x.d > y.d;
}
std::priority_queue<State> pque;
inline void dijkstra() {
    int e, v;
    // bool flag;
    State x;
    for (v = 2; v <= n; ++v)
        d[v] = INF;
    d[1] = 0;
    // has[1] = keys[1];
    pque.push((State){1, 0, has[1]});
    while (!pque.empty()) {
        x = pque.top();
        pque.pop();
        d[x.u] = std::min(d[x.u], x.d);
        for (e = adj[x.u]; e; e = next[e]) {
            if ((req[e] | x.s) == x.s) {
                v = to[e];
                // flag = false;
                if ((has[v] | x.s) != has[v]) {
                    has[v] |= x.s;
                    pque.push((State){v, d[x.u] + 1, x.s | keys[v]});
                }
                if (d[v] > d[x.u] + 1) {
                    d[v] = d[x.u] + 1;
                    pque.push((State){v, d[v], x.s | keys[v]});
                }
            }
        }
    }
}
*/
int d[MAXN][1 << 12];
std::queue<int> que;
bool inq[MAXN];
inline void work() {
    static int u, s, e, v;
    memset(d, 0x3f, sizeof(d));
    d[1][keys[1]] = 0;
    que.push(1);
    inq[1] = true;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        inq[u] = false;
        for (s = 0; s <= uni; ++s) {
            if ((s | keys[u]) == s) {
                for (e = adj[u]; e; e = next[e]) {
                    if ((s | req[e]) == s) {
                        v = to[e];
                        int &val = d[v][s | keys[v]];
                        if (d[u][s] + 1 < val) {
                            val = d[u][s] + 1;
                            if (!inq[v])
                                que.push(v), inq[v] = true;
                        }
                    }
                }
            }
        }
    }

}


int main() {
    int i, j, u, v, x, ans = INF;
    scanf("%d%d%d", &n, &m, &p);
    uni = (1 << p) - 1;
    for (i = 1; i <= n; ++i) {
        for (j = 0; j < p; ++j) {
            scanf("%d", &x);
            if (x)
                keys[i] |= 1 << j;
        }
    }
    for (i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        arc(u, v, i);
        for (j = 0; j < p; ++j) {
            scanf("%d", &x);
            if (x)
                req[i] |= 1 << j;
        }
    }
    work();
    for (i = 0; i <= uni; ++i)
        ans = std::min(ans, d[n][i]);
    if (ans >= INF)
        puts("No Solution");
    else
        printf("%d\n", ans);

    return 0;
}
