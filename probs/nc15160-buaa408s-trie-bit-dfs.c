#include <stdio.h>

#define re(i_, s_, t_) for (int i_ = s_; i_ < t_; ++i_)
#define N 502
#define S 10002
#define AKARI
 
typedef struct {
    int cnt, ch[S][26];
} Trie;
Trie trie1, trie2;

int insert(Trie *t, int o, int c) {
    int *u = &t->ch[o][c];
    if (!*u)
        *u = ++t->cnt;
    return *u;
}

int tim;
typedef struct {
    int c[S];
} BIT;
BIT bit1, bit2;

void add(BIT *t, int i, int v) {
    for (; i <= tim; i += i & -i)
        t->c[i] += v;
}

int qry(BIT *t, int i) {
    int r = 0;
    for (; i; i -= i & -i)
        r += t->c[i];
    return r;
}
 
typedef struct Node {
    int v;
    struct Node *n;
} Node;
Node pool[S], *curr = pool, *g[S];
void push(Node **u, int v) {
    Node *o = curr++;
    o->v = v;
    o->n = *u;
    *u = o;
}

int dfl[S], dfr[S];
void dfs1(int u) {
    int *c = trie2.ch[u];
    dfl[u] = ++tim;
    re (i, 0, 26) if (c[i])
        dfs1(c[i]);
    dfr[u] = tim;
}

int ans;
void dfs2(int u) {
    int v, *c = trie1.ch[u];
    for (Node *o = g[u]; o; o = o->n) {
        v = o->v;
        ans += qry(&bit1, dfr[v]) - qry(&bit1, dfl[v]) + qry(&bit2, dfl[v]);
        add(&bit1, dfl[v], 1);
        add(&bit2, dfl[v], 1);
        add(&bit2, dfr[v] + 1, -1);
    }
    re (i, 0, 26) if (c[i])
        dfs2(c[i]);
    for (Node *o = g[u]; o; o = o->n) {
        v = o->v;
        add(&bit1, dfl[v], -1);
        add(&bit2, dfl[v], -1);
        add(&bit2, dfr[v] + 1, 1);
    }
}

char s[N];
int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int o = 0, u;
        char *p = s;
        scanf("%s", s);
        for (o = 0; *p && *p != '#'; ++p)
            o = insert(&trie1, o, *p - 'a');
        u = o;
        while (*p)
            ++p;
        for (o = 0, --p; p >= s && *p != '#'; --p)
            o = insert(&trie2, o, *p - 'a');
        push(&g[u], o);
    }
    dfs1(0);
    dfs2(0);
    printf("%d\n", ans);
    return 0;
}
