#include <cstdio>
#include <climits>
#include <algorithm>
#include <vector>
#include <queue>

const int MAXV = 1004, MAXM = 5004;
int n;
struct Edge;
struct Node {
    struct Edge *adj, *cur, *prev;
    int dis, flow;
    bool inq;
} g[MAXV], *s, *t;
struct Edge {
    Node *u, *v;
    int cap, flow, cost;
    Edge *next, *rev;
    Edge(Node *_u, Node *_v, int _cap, int _cost) : u(_u), v(_v), cap(_cap), flow(0), cost(_cost), next(_u->adj) {}
};
bool bfs() {
    for (int i = 1; i <= n; ++i) {
        g[i].dis = 0;
        g[i].cur = g[i].adj;
    }
    std::queue<Node *> q;
    q.push(s);
    s->dis = 1;
    while (!q.empty()) {
        Node *u = q.front(), *v;
        q.pop();
        for (Edge *e = u->adj; e; e = e->next) {
            if (e->flow < e->cap && (v = e->v)->dis == 0) {
                v->dis = u->dis + 1;
                if (v == t)
                    return true;
                q.push(v);
            }
        }
    }
    return false;
}

int dfs(Node *u, int lim) {
    if (u == t || lim == 0)
        return lim;
    int res = 0, f;
    for (Edge *e = u->cur; e; e = e->next) {
        if (e->flow < e->cap && e->v->dis == u->dis + 1 && (f = dfs(e->v, std::min(lim, e->cap - e->flow))) > 0) {
            res += f;
            e->flow += f;
            e->rev->flow -= f;
            lim -= f;
            if (lim == 0)
                break;
        }
    }
    return res;
}
/*
int dfs(Node *u, int lim) {
    if (u == t || lim == 0)
        return lim;
    int f;
    for (Edge *e = u->cur; e; e = e->next) {
        if (e->flow < e->cap && e->v->dis == u->dis + 1 && (f = dfs(e->v, std::min(lim, e->cap - e->flow))) > 0) {
            e->flow += f;
            e->rev->flow -= f;
            return f;
        }
    }
    return 0;
}*/
void arc(int u, int v, int cap, int cost) {
    g[u].adj = new Edge(g + u, g + v, cap, cost);
    g[v].adj = new Edge(g + v, g + u, 0, -cost); // ypa!
    g[u].adj->rev = g[v].adj;
    g[v].adj->rev = g[u].adj;
}
int dinic() {
    int res = 0;
    while (bfs())
        res += dfs(s, INT_MAX);
    return res;
}
/*
int dinic() {
    int res = 0, f;
    while (bfs())
        while ((f = dfs(s, INT_MAX)) > 0)
            res += f;
    return res;
}*/
int mcmf() {
    int flow = 0, cost = 0;
    while (true) {
        for (int i = 1; i <= n; ++i) {
            g[i].prev = NULL;
            g[i].flow = 0;
            g[i].dis = INT_MAX;
            g[i].inq = false;
        }
        std::queue<Node *> q;
        q.push(s);
        s->flow = INT_MAX;
        s->dis = 0;
        s->inq = true;
        while (!q.empty()) {
            Node *u = q.front(), *v;
            q.pop();
            u->inq = false;
            for (Edge *e = u->adj; e; e = e->next) {
                if (e->flow < e->cap && (v = e->v)->dis > u->dis + e->cost) {
                    v->dis = u->dis + e->cost;
                    // printf("Flow %d, To %ld is %d\n", e->flow, v - g, v->dis);
                    v->prev = e;
                    v->flow = std::min(u->flow, e->cap - e->flow);
                    if (!v->inq) {
                        v->inq = true;
                        q.push(v);
                    }
                }
            }
        }
        if (t->dis == INT_MAX)
            break;
        for (Edge *e = t->prev; e; e = e->u->prev) {
            e->flow += t->flow;
            e->rev->flow -= t->flow;
        }
        flow += t->flow;
        cost += t->dis * t->flow;
    }
    return cost;
}
struct Triple {
    int u, v, w;
} te[MAXM];
int main() {
    static int m, k, u, v, c, w, i, mf;
    scanf("%d%d%d", &n, &m, &k);
    s = g + 1, t = g + n;
    ++n;
    for (i = 1; i <= m; ++i) {
        scanf("%d%d%d%d", &u, &v, &c, &w);
        arc(u, v, c, 0); // 
        te[i] = (Triple){u, v, w};
    }
    mf = dinic();
    for (i = 1; i <= m; ++i)
        arc(te[i].u, te[i].v, INT_MAX, te[i].w);
    arc(n, 1, k, 0);
    s = g + n;
    printf("%d %d\n", mf, mcmf());
    return 0;
}
