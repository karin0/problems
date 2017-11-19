#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

typedef long long ll;

const int MAXV = 3005;
const long long INF = 1L << 62;

int ce, cv;
struct Edge {
    int v;
    ll w;
};
std::vector<Edge> adj[MAXV];
std::vector<int> ca[MAXV];
inline void arc(int u, int v, ll w) {
    adj[u].push_back((Edge){v, w});
}
struct Record {
    int u;
    ll d;
};
inline bool operator < (const Record &x, const Record &y) {
    return x.d > y.d;
}
int safe[MAXV];
inline ll sssp() {
    static ll dis[MAXV], dop[MAXV], dr;
    static std::priority_queue<Record> pque;
    static bool vis[MAXV];
    static int i, u, v;
    for (i = 2; i <= cv; ++i)
        dis[i] = INF;
    // dis[1] = 0;
    pque.push((Record){1, 0});
    while (!pque.empty()) {
        u = pque.top().u;
        pque.pop();
        if (vis[u])
            continue;
        vis[u] = true;
        dr = std::max(dis[u], dop[u]);
        for (Edge *e = &adj[u].front(); e && e <= &adj[u].back(); ++e) {
            v = e -> v;
            if (dis[v] > dr + e -> w) {
                dis[v] = dr + e -> w;
                if (safe[v] <= 0)
                    pque.push((Record){v, std::max(dis[v], dop[v])});
            }
        }
        for (int *p = &ca[u].front(); p && p <= &ca[u].back(); ++p) {
            v = *p;
            dop[v] = std::max(dop[v], dr); // ***
            --safe[v];
            if (safe[v] <= 0)
                pque.push((Record){v, std::max(dis[v], dop[v])});
        }
    }
    return std::max(dis[cv], dop[cv]);
}

int main() {
    int i, j, u, v, x;
    ll w;
    scanf("%d%d", &cv, &ce);
    for (i = 1; i <= ce; ++i) {
        scanf("%d%d%lld", &u, &v, &w);
        if (u != v) // ***
            arc(u, v, w);
    }
    for (i = 1; i <= cv; ++i) {
        scanf("%d", &x);
        safe[i] = x;
        for (j = 1; j <= x; ++j) {
            scanf("%d", &u);
            ca[u].push_back(i); // **
        }
    }
    
    printf("%lld\n", sssp());
    return 0;
}
