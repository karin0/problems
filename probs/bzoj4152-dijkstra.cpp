#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

typedef long long ll;
const int MAXN = 200005, INF = 0x3f3f3f3f;
struct Item {
    int u, x, y;
} pt[MAXN];
inline bool qaqx(const Item &a, const Item &b) {
    return a.x < b.x;
}
inline bool qaqy(const Item &a, const Item &b) {
    return a.y < b.y;
}
int n, m, xx[MAXN], yx[MAXN];
struct Edge {
    int v, w;
    Edge *next;
} se[MAXN << 2];
Edge *adj[MAXN];
inline void arc(int u, int v, int w) {
    Edge &e = se[++m];
    e.v = v;
    e.w = w;
    e.next = adj[u];
    adj[u] = se + m;
}

ll d[MAXN];
struct Dijk {
    int u;
    ll d;
};
bool operator < (const Dijk &u, const Dijk &v) {
    return u.d > v.d;
}
std::priority_queue<Dijk> pque;
ll dijkstra() {
    static int u, v;
    static Dijk uu;
    std::fill(d + 1, d + n + 1, INF);
    d[1] = 0;
    pque.push((Dijk){1, 0});
    while (!pque.empty()) {
        uu = pque.top();
        pque.pop();
        u = uu.u;
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            if (d[v] > d[u] + e->w)
                d[v] = d[u] + e->w, pque.push((Dijk){v, d[v]});
        }
    }
    return d[n];
}

int main() {
    static int i;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%d%d", xx + i, yx + i);
        pt[i].u = i;
        pt[i].x = xx[i];
        pt[i].y = yx[i];
    }
    std::sort(pt + 1, pt + n + 1, qaqx);
    for (i = 1; i < n; ++i) {
        if (pt[i + 1].x - pt[i].x <= std::abs(pt[i].y - pt[i + 1].y)) {
            arc(pt[i].u, pt[i + 1].u, pt[i + 1].x - pt[i].x);
            arc(pt[i + 1].u, pt[i].u, pt[i + 1].x - pt[i].x);
        }
    }
    std::sort(pt + 1, pt + n + 1, qaqy);
    for (i = 1; i < n; ++i) {
        if (pt[i + 1].y - pt[i].y < std::abs(pt[i].x - pt[i + 1].x)) {
            arc(pt[i].u, pt[i + 1].u, pt[i + 1].y - pt[i].y);
            arc(pt[i + 1].u, pt[i].u, pt[i + 1].y - pt[i].y);
        }
    }
    printf("%lld\n", dijkstra());
    return 0;
}
