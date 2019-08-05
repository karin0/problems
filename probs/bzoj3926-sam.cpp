#include <cstdio>
#include <new>

const int SIGMA = 10;
const int MAXN = 100001;

struct SAM {
    struct State {
        State *ch[SIGMA], *next;
        int max;
    } *start, _pool[MAXN * 20 * 2], *_curr;
    State *_new(int x) {
        _curr->max = x;
        return _curr++;
    }
    SAM () {
        _curr = _pool;
        start = _new(0);
    }
    State *insert(State *o, int c) {
        static State *u, *p, *q;
        static int i;
        if (o->ch[c] && o->ch[c]->max == o->max + 1)
            return o->ch[c];
        u = _new(o->max + 1);
        while (o && !o->ch[c])
            o->ch[c] = u, o = o->next;
        if (!o)
            u->next = start;
        else if (o->ch[c]->max == o->max + 1)
            u->next = o->ch[c];
        else {
            p = o->ch[c];
            q = _new(o->max + 1);
            for (i = 0; i < SIGMA; ++i)
                q->ch[i] = p->ch[i];
            q->next = p->next;
            p->next = u->next = q;
            for (; o && o->ch[c] == p; o = o->next)
                o->ch[c] = q; //puts("233");
        }
        return u;
    }
} sam;


struct Node {
    struct Edge *adj;
    int c, deg;
} g[MAXN];
struct Edge {
    Node *v;
    Edge *next;
} _pool[MAXN * 2], *_curr;
Edge *_new(Node *u, Node *v) {
    _curr->v = v;
    _curr->next = u->adj;
    return _curr++;
}
void arc(int u, int v) {
    g[u].adj = _new(g + u, g + v);
}
void dfs(Node *u, Node *fa, SAM::State *pos) {
    pos = sam.insert(pos, u->c);
    for (Edge *e = u->adj; e; e = e->next)
        if (e->v != fa)
            dfs(e->v, u, pos);
}

int main() {
    static int n, m, i, u, v;
    static long long ans;
    _curr = _pool;
    scanf("%d%d", &n, &m);
    for (i = 1; i <= n; ++i)
        scanf("%d", &g[i].c);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        ++g[u].deg;
        ++g[v].deg;
        arc(u, v);
        arc(v, u);
    }
    for (i = 1; i <= n; ++i)
        if (g[i].deg == 1)
            dfs(g + i, NULL, sam.start);
    for (SAM::State *s = sam._pool + 1; s != sam._curr; ++s)
        ans += s->max - s->next->max;
    printf("%lld\n", ans);

    return 0;
}
