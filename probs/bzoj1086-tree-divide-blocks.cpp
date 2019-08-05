#include <cstdio>

const int N = 1005;
struct Node {
    struct Edge *e;
    int bel;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge (Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
};
int n, s, bcnt, cent[N], ssz;
Node *sta[N];
void dfs(Node *u, Node *f) {
    int osz = ssz;
    for (Edge *e = u->e; e; e = e->e) {
        if (e->v == f)
            continue;
        dfs(e->v, u);
        if (ssz - osz >= s) {
            ++bcnt;
            while (ssz != osz)
                sta[--ssz]->bel = bcnt;
            cent[bcnt] = u - g;
        }
    }
    sta[ssz++] = u;
}
void make() {
    dfs(&g[1], NULL);
    while (ssz)
        sta[--ssz]->bel = bcnt;
}
int main() {
    static int i, u, v;
    scanf("%d%d", &n, &s);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        new Edge(&g[u], &g[v]);
        new Edge(&g[v], &g[u]);
    }
    make();
    printf("%d\n", bcnt);
    for (i = 1; i <= n; ++i)
        printf("%d ", g[i].bel);
    putchar('\n');
    for (i = 1; i <= bcnt; ++i)
        printf("%d ", cent[i]);
    putchar('\n');

    return 0;
}
