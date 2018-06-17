#include <cstdio>
#include <vector>
#include <algorithm>
const int MAXN = 450, MAXM = 15050;
const int INF = 2147483647;

int n, m, s, t, res_flow, res_cost;
struct Node {
    std::vector<struct Edge> adj;
    int dist, flow;
    Edge* pre;
    bool in_que;
} nodes[MAXN];
struct Edge {
    Node *from, *to;
    int cap, flow, cost, rev;
    Edge(Node *from, Node *to, int cap, int cost, int rev): from(from), to(to), cap(cap), flow(0), cost(cost), rev(rev) {}
};
inline void add_edge(int u, int v, int c, int w) {
    nodes[u].adj.push_back(Edge(&nodes[u], &nodes[v], c, w, nodes[v].adj.size()));
    nodes[v].adj.push_back(Edge(&nodes[v], &nodes[u], 0, -w, nodes[u].adj.size() - 1));
}

Node *que[MAXN * MAXN]; // 一个点最大可能入队 n 次
inline bool spfa() {
    int front = 1, back = 0;
    Node *u, *v;
    for (u = &nodes[1]; u <= &nodes[n]; ++u) {
        u -> dist = INF;
        u -> in_que = false;
    }
    u = &nodes[s];
    u -> dist = 0;
    u -> pre = NULL;
    u -> flow = INF;
    que[++back] = u;
    u -> in_que = true;

    while (front <= back) {
        u = que[front++];
        u -> in_que = false;
        for (Edge* e = &u -> adj.front(); e <= &u -> adj.back(); ++e) {
            if ((v = e -> to) -> dist > u -> dist + e -> cost && e -> cap > e -> flow) {
                v -> dist = u -> dist + e -> cost;
                v -> pre = e;
                v -> flow = std::min(u -> flow, e -> cap - e -> flow);
                if (!v -> in_que) {
                    que[++back] = v;
                    if (v -> dist < que[front] -> dist)
                        std::swap(que[front], que[back]); // SLF
                    v -> in_que = true;
                }
            }
        }
    }
    return nodes[t].dist < INF;
}
inline void mcmf() {
    // flow = cost = 0;
    Node *pt = &nodes[t];
    while (spfa()) {
        for (Edge *e = pt -> pre; e; e = e -> from -> pre) {
            e -> flow += pt -> flow;
            e -> to -> adj[e -> rev].flow -= pt -> flow;
        }
        res_flow += pt -> flow;
        res_cost += pt -> flow * pt -> dist;
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
