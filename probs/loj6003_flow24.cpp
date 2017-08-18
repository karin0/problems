#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define SP(x) ((((x) << 1)) | 1) // 2 * x + 1
#define TP(x) (((x) + 1) << 1) // 2 * x + 2
#define TNO(x) (((x) >> 1) - 1) // TP(TNO(x)) == x
const int MAXV = 5000; // idk what it should be.
const int G = 1900;
const int INF = 2147483647;

int n, s, t, max_flow;
struct Node {
    std::vector<struct Edge> adj;
    struct Edge* cur;
    int dist;
} nodes[MAXV];
struct Edge {
    Node* to;
    int cap, flow, re:
    Edge(Node* to, int cap, int rev): to(to), cap(cap), flow(0), rev(rev) {}
};
inline void add_edge(int u, int v, int c) {
    nodes[u].adj.push_back(Edge(&nodes[v], c, nodes[v].adj.size()));
    nodes[v].adj.push_back(Edge(&nodes[u], 0, nodes[u].adj.size() - 1));
}
inline void remove_edges(int u) { // 移除与 u 相连的所有边
    for (Edge *e = &nodes[u].adj.front(); e && e <= &nodes[u].adj.back(); ++e) {
        e -> cap = 0;
        e -> to -> adj[e -> rev].cap = 0;
    }
}

Node* que[MAXV];
inline bool bfs() {
    int front = 1, back = 0;
    Node *u, *v;
    for (u = &nodes[1]; u <= &nodes[n]; ++u)
        u -> dist = 0;
    que[++back] = &nodes[s];
    nodes[s].dist = 1;
    
    while (front <= back) {
        u = que[front++];
        for (Edge *e = &(u -> adj.front()); e && e <= &(u -> adj.back()); ++e)
            if (!((v = e -> to) -> dist) && e -> cap > e -> flow)  {
                v -> dist = u -> dist + 1;
                que[++back] = v;
            }
    }
    return nodes[t].dist;
}
int dfs(Node* u, int a) {
    if (u == &nodes[t] || a == 0)
        return a;
    int res = 0, f;
    Node* v;
    for (Edge *&e = u -> cur; e && e <= &(u -> adj.back()); ++e) {
        v = e -> to;
        if (u -> dist + 1 == v -> dist && e -> cap > e -> flow && (f = dfs(v, std::min(a, e -> cap - e -> flow))) > 0) {
            res += f;
            a -= f;
            e -> flow += f;
            v -> adj[e -> rev].flow -= f;
            if (a == 0)
                break;
        }
    }
    return res;
}
inline void dinic() {
    int i;
    Node *sp = &nodes[s], *u;
    while (bfs()) {
        for (i = 1; i <= n; ++i) {
            u = &nodes[i];
            u -> cur = &(u -> adj.front());
        }
        max_flow += dfs(sp, INF); // 动态加边,需要全局维护最大流
    }
}

bool is_squared[G * G + 5];
int next[MAXV], prev[MAXV];
int main() {
    int k, i, j, ans;
    scanf("%d", &k);
    for (i = 1; i <= G; ++i)
        is_squared[i * i] = true;
    s = 1, t = 2; //n = 2;
    for (i = 1; ; ++i) { // 放 1 .. i 的球
        n = TP(i);
        add_edge(s, SP(i), 1);
        add_edge(TP(i), t, 1); // 维护二分图和参数 s, n, t
        for (j = 1; j < i; ++j)
            if (is_squared[j + i])
                add_edge(SP(j), TP(i), INF);
        dinic(); // 最小路径覆盖 = i - max_flow, 要得到使得 i - max_flow == k 的最大 i
        if (i - max_flow > k)
            break;
    }
    printf("%d\n", ans = i - 1);

    // 重构 i = ans 时的网络,需要删除多余的点 SP(ans - 1), TP(ans - 1) 以及与之相连的边
    remove_edges(SP(ans + 1));
    remove_edges(TP(ans + 1));
    n = TP(ans);
    // max_flow = 0; // 不需要还原流量
    dinic();
    for (i = 1; i <= ans; ++i)
        for (Edge *e = &nodes[SP(i)].adj.front(); e && e <= &nodes[SP(i)].adj.back(); ++e)
            if (e -> cap == INF && e -> flow == 1) {
                next[i] = TNO(e -> to - nodes);
                prev[next[i]] = i;
            } // 有的路径只包含一个点

    for (i = 1; i <= ans; ++i)
        if (prev[i] == 0) {
            for (j = i; j; j = next[j])
                printf("%d ", j);
            printf("\n");
        }
    
    return 0;
}
