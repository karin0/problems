#include <cstdio>
#include <cctype>
#include <algorithm>

typedef long long ll;
const int N = 3000003;
int n;
struct Node {
    bool vis;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
};// pool[N * 4], *curr = pool;
/*
void dfs(Node *u) {
    printf("%ld here, et = %d\n", u-g, etlen);
    st[0][u->etn = ++etlen] = u;
    for (Edge *e = u->e; e; e = e->e) if (!e->v->dep) {
        e->v->dep = u->dep + 1;
        dfs(e->v);
        st[0][++etlen] = u;
    }
}*/
void dfs(Node *const u) {
    static int tim = 0;
    u->vis = true;
    printf("%ld here, tim = %d\n", u-g, ++tim);
    for (Edge *e = u->e; e; e = e->e) if (!e->v->vis) {
        // e->v->dep = u->dep + 1;
        printf("TO %ld \n", e->v - g);
        dfs(e->v);
    }
}
int main() {
    static int i, u, v;
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        new Edge(&g[u], &g[v]);
        new Edge(&g[v], &g[u]);
    }
    dfs(&g[1]);
    puts("Done");

    return 0;
}
