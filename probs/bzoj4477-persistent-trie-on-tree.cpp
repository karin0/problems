#include <cstdio>
#include <algorithm>
#include <new>
const int N = 100005, SIGMA = 'z' - 'a' + 1;
struct Trie *currt;
struct Trie {
    Trie *ch[SIGMA];
    int cnt;
    Trie() {}
    Trie *insert(const char *s) const {
        Trie *o = new (currt++) Trie(*this);
        ++o->cnt;
        if (*s) {
            int c = *s - 'a';
            if (ch[c])
                o->ch[c] = ch[c]->insert(s + 1);
            else
                o->ch[c] = (new (currt++) Trie)->insert(s + 1);
        }
        return o;
    }
} poolt[N * 13 * 2];
struct Node {
    int efn, dep;
    Trie *t;
    struct Edge *e;
} g[N], *st[19][N * 2]; // ****
struct Edge {
    Node *v;
    Edge *e;
    char *s;
} poole[N * 2], *curre = poole;
void arc(Node *u, Node *v, char *s) {
    *curre = (Edge){v, u->e, s};
    u->e = curre++;
}
int eim;
void dfs(Node *u) {
    st[0][++eim] = u;
    u->efn = eim;
    Node *v;
    for (Edge *e = u->e; e; e = e->e) {
        if (!(v = e->v)->dep) {
            v->t = u->t->insert(e->s);
            v->dep = u->dep + 1;
            dfs(v);
            st[0][++eim] = u;
        }
    }
}
int lg[N * 2];
inline Node *min(Node *u, Node *v) {
    return u->dep < v->dep ? u : v;
}
void init() {
    static int i, j;
    g[1].t = new (currt++) Trie;
    g[1].dep = 1;
    dfs(&g[1]);
    for (i = 2; i <= eim; ++i)
        lg[i] = lg[i - 1] + ((1 << (lg[i - 1] + 1)) <= i); // printf("lg[%d]=%d\n",i,lg[i]);
    for (j = 1; (1 << j) <= eim; ++j)
        for (i = 1; i + (1 << j) - 1 <= eim; ++i)
            st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
}
Node *lca(const Node *u, const Node *v) {
    static int l, r, k;
    l = u->efn, r = v->efn;
    if (l > r)
        std::swap(l, r);
    k = lg[r - l + 1];
    return min(st[k][l], st[k][r - (1 << k) + 1]);
}
inline int query(const Node *u, char *s) {
    // printf("Ask %s\n",s);
    Trie *o;
    char *p = s;
    for (o = u->t; *p && o; o = o->ch[*p - 'a'], ++p);
    return o ? o->cnt : 0;
}
inline int query(const Node *u, const Node *v, char *s) {
    // printf("Lca of %d, %d is %d\n",u-g,v-g,lca(u,v)-g);
    return query(u, s) + query(v, s) - 2 * query(lca(u, v), s);
}

int main() {
    static int n, m, u, v, i;
    static char s[16], ss[N][15], *p;
    currt = poolt;
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        p = ss[i];
        scanf("%d%d%s", &u, &v, p);
        arc(&g[u], &g[v], p);
        arc(&g[v], &g[u], p);
    }
    init();
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d%s", &u, &v, s);
        printf("%d\n", query(&g[u], &g[v], s));
    }
    return 0;
}
