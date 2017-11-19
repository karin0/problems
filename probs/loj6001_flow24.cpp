#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int MAXV = 150;
const int INF = 2147483647;

int n, s, t;
struct Node {
    std::vector<struct Edge> adj;
    struct Edge* cur;
    int dist;
} nodes[MAXV];
struct Edge {
    Node* to;
    int cap, rev;
    Edge(Node* to, int cap, int rev): to(to), cap(cap), rev(rev) {}
};
inline void add_edge(int u, int v, int c) {
    nodes[u].adj.push_back(Edge(&nodes[v], c, nodes[v].adj.size()));
    nodes[v].adj.push_back(Edge(&nodes[u], 0, nodes[u].adj.size() - 1));
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
        for (Edge *e = &(u -> adj.front()); e <= &(u -> adj.back()); ++e)
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
                break;
        }
    }
    return res;
}
inline int dinic() {
    int f = 0, i;
    Node *sp = &nodes[s], *u;
    while (bfs()) {
        for (i = 1; i <= n; ++i) {
            u = &nodes[i];
            u -> cur = &(u -> adj.front());
        }
        f += dfs(sp, INF);
    }
    return f;
}

bool read(int &res) {
    res = 0;
    register char ch = 0;
    while (ch < '0' || ch > '9') {
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        res = res * 10 + (ch - '0');
        ch = getchar();
    }
    return ch != '\n' && ch != '\r';
}

int main() {
    int e_card, i_card, u, r, p_sum = 0, ans;
    read(e_card);
    read(i_card);
    n = e_card + i_card;
    s = n + 1;
    t = n + 2;
    for (u = 1; u <= e_card; ++u) {
        if (read(r)) {
            add_edge(s, u, r);
            p_sum += r;
        } else {
            add_edge(s, u, r);
            p_sum += r;
            continue;
        } // 防止 R(i) = ∅ 时出错
        while (read(r)) {
            add_edge(u, e_card + r, INF);
        }
        add_edge(u, e_card + r, INF);
    }
    for (u = e_card + 1; u <= n; ++u) {
        read(r);
        add_edge(u, t, r);
    }
    n += 2;
    ans = p_sum - dinic();
    n -= 2;
    
    // 仅有最后在 bfs 过程中仍能访问到的点在最小割的 S 集合中
    for (u = 1; u <= e_card; ++u)
        if (nodes[u].dist)
            printf("%d ", u);
    printf("\n");
    for (u = e_card + 1; u <= n; ++u)
        if (nodes[u].dist)
            printf("%d ", u - e_card);
    printf("\n%d\n", ans);

    return 0;
}
