#include <cstdio>
#include <queue>

const int MAXV = 100005, MAXE = 100005;

int cv, ce;
struct Edge {
    int v;
    Edge *next;
} se[MAXE];
Edge *adj[MAXV];
inline void arc(int u, int v, int e) {
    se[e].v = v;
    se[e].next = adj[u];
    adj[u] = se + e;
}
int ind[MAXV], seq[MAXV], cnt;
void solve() {
    static int u, v, i;
    std::priority_queue<int, std::vector<int>, std::less<int> > pque;
    for (u = 1; u <= cv; ++u)
        if (ind[u] == 0)
            pque.push(u);
    while (!pque.empty()) {
        u = pque.top();
        pque.pop();
        seq[++cnt] = u;
        for (Edge *e = adj[u]; e; e = e->next) {
            v = e->v;
            --ind[v];
            if (ind[v] == 0)
                pque.push(v);
        }
    }
    if (cnt == cv) {
        for (i = cnt; i >= 1; --i)
            printf("%d ", seq[i]);
        putchar('\n');
    } else
        puts("Impossible!");
}
inline void reset() {
    static int i;
    cnt = 0;
    for (i = 1; i <= cv; ++i)
        ind[i] = 0, adj[i] = 0;
}

int main() {
    int t, kase, u, v, i;
    scanf("%d", &t);
    for (kase = 1; kase <= t; ++kase) {
        scanf("%d%d", &cv, &ce);
        for (i = 1; i <= ce; ++i)
            scanf("%d%d", &v, &u), arc(u, v, i), ++ind[v];
        solve();
        if (kase != t)
            reset();
    }

    return 0;
}
