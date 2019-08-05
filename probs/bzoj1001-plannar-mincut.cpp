#include <cstdio>
#include <vector>
#include <queue>
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))

const int N = 1003, V = N * N * 2, INF = 0x3f3f3f3f;
int n, m, cv, dis[V];
struct Edge {
    int v, w;
};
std::vector<Edge> g[V];
void arc(int u, int v, int w) {
    g[u].push_back((Edge){v, w});
    g[v].push_back((Edge){u, w});
}
struct Akari {
    int u, dis;
    bool operator < (const Akari &rhs) const {
        return dis > rhs.dis;
    }
};
void dijkstra(int s) {
    static std::priority_queue<Akari> pq;
    static int u, v, t;
    for (u = 0; u < cv; ++u)
        dis[u] = INF;
    pq.push((Akari){s, dis[s] = 0});
    while (!pq.empty()) {
        u = pq.top().u;
        pq.pop();
        for (std::vector<Edge>::iterator it = g[u].begin(); it != g[u].end(); ++it) {
            v = it->v, t = dis[u] + it->w;
            if (dis[v] > t)
                pq.push((Akari){v, dis[v] = t});
        }
    }
}
int s, t;
int p(const int i, const int j, const int k) {
    if (i < 0 || j >m-2)
        return s;
    if (i > n - 2 || j <0)
        return t;
    return (i * (m - 1) + j) << 1 | k;
}
int main() {
    static int i, j, x;
    scanf("%d%d", &n, &m);
    cv = p(n - 2, m - 2, 1) + 3;
    s = cv - 1, t = cv - 2;
    re (i, 0, n) re (j, 0, m - 1) {
        scanf("%d", &x);
        arc(p(i, j, 0), p(i - 1, j, 1), x);
    }
    re (i, 0, n - 1) re (j, 0, m) {
        scanf("%d", &x);
        arc(p(i, j, 1), p(i, j - 1, 0), x);
    }
    re (i, 0, n - 1) re (j, 0, m - 1) {
        scanf("%d", &x);
        arc(p(i, j, 0), p(i, j, 1), x);
    }
    dijkstra(s);
    printf("%d\n", dis[t]);

    return 0;
}
