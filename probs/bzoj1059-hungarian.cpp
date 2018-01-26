#include <cstdio>

const int N = 202;
int n, w; // w 是一边的点数，此处两边都有 w 个点
struct Node {
    struct Edge *e;
    bool used;
    Node *match;
} g[N << 1];
struct Edge {
    Node *v;
    Edge *next;
} se[(N << 1) * (N << 1)];
int ecnt;
void arc(Node *u, Node *v) {
    Edge &e = se[++ecnt];
    e.v = v, e.next = u->e, u->e = &e;
}
bool dfs(Node *u) {
    for (Edge *e = u->e; e; e = e->next) {
        Node *v = e->v;
        if (!v->used) {
            v->used = true;
            if (v->match == NULL || dfs(v->match)) {
                v->match = u;
                u->match = v;
                return true;
            }
        }
    }
    return false;
}
int hungarian() {
    int res = 0, i;
    for (i = 1; i <= n; ++i)
        g[i].match = NULL;
    for (Node *u = &g[1]; u <= &g[w]; ++u)
        if (u->match == NULL) {
            for (i = 1; i <= n; ++i)
                g[i].used = false;
            if (dfs(u))
                ++res;
        }
    return res;
}

int main() {
    static int t, x, i, j;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &w);
        n = w << 1;
        for (i = 1; i <= w; ++i)
            for (j = 1; j <= w; ++j)
                if (scanf("%d", &x), x)
                    arc(&g[i], &g[w + j]), arc(&g[w + j], &g[i]);
        puts(hungarian() == w ? "Yes" : "No");
        if (t) {
            ecnt = 0;
            for (i = 1; i <= n; ++i)
                g[i].e = NULL;
        }
    }

    return 0;
}
