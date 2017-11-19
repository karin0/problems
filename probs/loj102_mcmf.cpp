#include <cstdio>
#include <vector>
#include <algorithm>
const int MAXN = 450, MAXM = 15050;
const int INF = 2147483647;

int n, m, s, t, res_flow, res_cost;
struct Edge {
    int from, to, cap, flow, cost, rev;
    Edge(int from, int to, int cap, int cost, int rev): from(from), to(to), cap(cap), flow(0), cost(cost), rev(rev) {}
};
std::vector<Edge> adj[MAXN];
void add_edge(int u, int v, int c, int w) {
    adj[u].push_back(Edge(u, v, c, w, adj[v].size()));
    adj[v].push_back(Edge(v, u, 0, -w, adj[u].size() - 1));
}

int que[MAXN * MAXN], dist[MAXN], flow[MAXN];
Edge* pre[MAXN]; // 一个点最大可能入队 n 次
bool in_que[MAXN];
inline bool spfa() {
    int front = 1, back = 0;
    std::fill(dist + 1, dist + n + 1, INF);
    std::fill(in_que + 1, in_que + n + 1, false);
    dist[s] = 0;
    pre[s] = NULL;
    flow[s] = INF;
    que[++back] = s;
    in_que[s] = true;

    int u, v;
    while (front <= back) {
        u = que[front++];
        in_que[u] = false;
        for (Edge* e = &adj[u].front(); e <= &adj[u].back(); ++e) {
            if (dist[v = (e -> to)] > dist[u] + e -> cost && e -> cap > e -> flow) {
                dist[v] = dist[u] + e -> cost;
                pre[v] = e;
                flow[v] = std::min(flow[u], e -> cap - e -> flow);
                if (!in_que[v]) {
                    que[++back] = v;
                    in_que[v] = true;
                }
            }
        }
    }
    return dist[t] < INF;
}
inline void mcmf() {
    // flow = cost = 0;
    while (spfa()) {
        for (Edge *e = pre[t]; e; e = pre[e -> from]) {
            e -> flow += flow[t];
            adj[e -> to][e -> rev].flow -= flow[t];
        }
        res_flow += flow[t];
        res_cost += flow[t] * dist[t];
    }
}

inline void read(int& res) {
    res = 0;
    char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        res = (res << 3) + (res << 1) + (ch - '0');
        ch = getchar();
    }
    // scanf("%d", &res);
}

int main() {
    read(n);
    read(m);
    int u, v, c, w;
    s = 1;
    t = n;
    for (int i = 0; i < m; ++i) {
        read(u);
        read(v);
        read(c);
        read(w);
        add_edge(u, v, c, w);
    }
    mcmf();
    printf("%d %d\n", res_flow, res_cost);
    return 0;
}
