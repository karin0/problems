#include <cstdio>
#include <queue>

typedef long long ll;
const int MAXN = 100005, MAXE = 500007, INF = 0x3f3f3f3f;
int n, ecnt;
struct Edge {
    int v, w;
    Edge *next;
} se[MAXE], *adj[MAXN];
inline void arc(int u, int v, int w) {
    Edge &e = se[++ecnt];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = &e;
}
ll d[MAXN];
bool spfa(int s) {
    static std::queue<int> que;
    static bool inq[MAXN];
    static int cnt[MAXN], u, v;
    for (u = 1; u <= n; ++u)
        d[u] = INF;
    d[s] = 0;
    que.push(s);
    inq[s] = true;
    cnt[s] = 1;
    while (!que.empty()) {
        u = que.front();
        que.pop();
        inq[u] = false;
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            if (d[v] > d[u] + e->w) {
                d[v] = d[u] + e->w;
                if (!inq[v]) {
                    que.push(v);
                    inq[v] = true;
                    ++cnt[v];
                    if (cnt[v] > n)
                        return false;
                }
            }
        }
    }
    return true;
}
int main() {
    static int i, m, opt, u, v, s;
    static ll ans;
    scanf("%d%d", &n, &m);
    s = n + 1;
    ++n;
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d", &opt, &u, &v);
        if (u == v && (opt & 1) == 0) {
            puts("-1");
            return 0;
        }
        if (opt == 1) // a[u] = a[v]: d[u] - d[v] <= 0, d[v] - d[u] <= 0
            arc(u, v, 0), arc(v, u, 0);
        else if (opt == 2) // a[u] < a[v]: a[u] + 1 <= a[v]: d[u] - d[v] <= -1
            arc(u, v, -1);
        else if (opt == 3) // a[u] >= a[v]
            arc(v, u, 0);
        else if (opt == 4)
            arc(v, u, -1);
        else
            arc(u, v, 0);
    }
    for (i = n - 1; i >= 1; --i)
        arc(s, i, -1);
    if (spfa(s)) {
        for (i = 1; i < n; ++i)
            ans -= d[i];
        printf("%lld\n", ans);
    } else
        puts("-1");

    return 0;
}
