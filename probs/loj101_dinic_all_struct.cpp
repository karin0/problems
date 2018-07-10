#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int MAXN = 1000050;
const int INF = 2147483647; // c <= 2 ^ 31 - 1

int n, m, s, t;
struct Node {
    std::vector<struct Edge> adj;
    struct Edge* cur;
    int dist;
} nodes[MAXN];
struct Edge {
    Node* to;
    int cap, rev; // rev 是反向边在其起点的邻接表中的下标
    Edge(Node* to, int cap, int rev): to(to), cap(cap), rev(rev) {}
};
inline void add_edge(int u, int v, int c) {
    nodes[u].adj.push_back(Edge(&nodes[v], c, nodes[v].adj.size()));
    nodes[v].adj.push_back(Edge(&nodes[u], 0, nodes[u].adj.size() - 1));
}

Node* que[MAXN];
inline bool bfs() {
    int front = 1, back = 0; // 手动队列
    Node *u, *v;
    for (u = &nodes[1]; u <= &nodes[n]; ++u)
        u -> dist = 0;
    que[++back] = &nodes[s];
    nodes[s].dist = 1; // 不用特判
    
    while (front <= back) {
        u = que[front++];
        for (Edge *e = &(u -> adj.front()); e <= &(u -> adj.back()); ++e) // 这比用迭代器遍历更快
            if (!((v = e -> to) -> dist) && e -> cap > 0)  {
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
    for (Edge *&e = u -> cur; e <= &(u -> adj.back()); ++e) {
        v = e -> to;
        if (u -> dist + 1 == v -> dist && e -> cap > 0 && (f = dfs(v, std::min(a, e -> cap))) > 0) {
            res += f;
            a -= f;
            e -> cap -= f;
            v -> adj[e -> rev].cap += f;
            if (a == 0)
                break; // 及时跳出
        }
    }
    return res;
}
inline int dinic() {
    int f = 0, i;
    Node *sp = &nodes[s], *u;
    while (bfs()) {
        // printf("%d\n", nodes[t].dist);
        for (i = 1; i <= n; ++i) {
            u = &nodes[i];
            u -> cur = &(u -> adj.front());
        } // 需在 bfs 前进行初始化
        f += dfs(sp, INF);
    }
    return f;
}

void read(int &res) {
    res = 0;
    register char ch = 0;
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9') {
        // res = res * 10 + (ch - '0');
        res = (res << 3) + (res << 1) + (ch - '0');
        ch = getchar();
    }
}

int main() {
    int u, v, c, i;
    read(n);
    read(m);
    read(s);
    read(t);
    
    for (i = 0; i < m; ++i) {
        read(u);
        read(v);
        read(c);
        add_edge(u, v, c);
    }
    printf("%d\n", dinic());
    return 0;
}
