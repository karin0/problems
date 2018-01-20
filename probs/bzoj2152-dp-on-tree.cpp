#include <cstdio>
#include <algorithm>

const int N = 20003;
struct Node {
    struct Edge *e;
    int siz, dep, f[3];
} g[N];
struct Edge {
    Node *v;
    int w;
    Edge *next;
    Edge(Node *_u, Node *_v, int _w) : v(_v), w(_w), next(_u->e) {
        _u->e = this;
    }
};
int n;

int ans;
void dfs(Node *u, Node *f) {
    int i;
    u->f[0] = 1;
    for (Edge *e = u->e; e; e = e->next)
        if (e->v != f) {
            dfs(e->v, u);
            for (i = 0; i < 3; ++i)
                u->f[(i + e->w) % 3] += e->v->f[i];
            // for (i = 0; i < 3; ++i)
            ans -= e->v->f[(6 - e->w) % 3] * e->v->f[(6 - e->w) % 3] + e->v->f[(7 - e->w) % 3] * e->v->f[(8 - e->w) % 3] * 2;
        }
    ans += u->f[0] * u->f[0] + u->f[1] * u->f[2] * 2;
}
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
    static int i, u, v, w, k;
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        w %= 3;
        new Edge(g + u, g + v, w);
        new Edge(g + v, g + u, w);
    }
    dfs(g + 1, NULL);
    k = gcd(ans, n * n);
    printf("%d/%d\n", ans / k, n * n / k);
    return 0;
}
