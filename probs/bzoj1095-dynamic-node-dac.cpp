#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 200005;
struct Heap {
    std::priority_queue<int> q, d;
    inline void clean() {
        while (!q.empty() && !d.empty() && q.top() == d.top())
            q.pop(), d.pop();
    }
    inline void insert(const int x) {
        if (x >= 0)
            q.push(x);
    }
    inline void remove(const int x) {
        if (x >= 0)
            d.push(x);
    }
    inline int size() {
        return q.size() - d.size();
    }
    inline int top() {
        clean();
        return q.empty() ? -1234567 : q.top();
    }
    inline void pop() {
        clean();
        if (!q.empty())
            q.pop();
    }
    inline int top2() {
        static int t, tt;
        t = top();
        pop();
        tt = top();
        insert(t);
        return t + tt;
    }
} th;
struct Node {
    struct Edge *e, *de;
    int siz, ms, dep, deu;
    bool done, ok;
    Node *dfa;
    Heap dh1, dh2;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge(Node *_v, Edge *_e) : v(_v), e(_e) {}
};
void arc(Node *u, Node *v) {
    u->e = new Edge(v, u->e);
}
void darc(Node *u, Node *v) {
    u->de = new Edge(v, u->de);
    v->dfa = u;
}
int n, ocnt;
Node *a[N];
int cnt;
void dfs1(Node *u, Node *f) {
    a[++cnt] = u;
    u->siz = 1, u->ms = 0;
    for (Edge *e = u->e; e; e = e->e)
        if (e->v != f && !e->v->done) {
            dfs1(e->v, u);
            u->siz += e->v->siz;
            u->ms = std::max(u->ms, e->v->siz);
        }
}
Node *center(Node *u) {
    cnt = 0;
    dfs1(u, NULL);
    Node *res = u;
    for (int i = 1; i <= cnt; ++i) {
        a[i]->ms = std::max(a[i]->ms, u->siz - a[i]->ms);
        if (res->ms > a[i]->ms)
            res = a[i];
    }
    return res;
}
Node *st[N << 1][22];
int teu;
void dfs0(Node *u) {
    st[++teu][0] = u;
    u->deu = teu;
    for (Edge *e = u->e; e; e = e->e)
        if (!e->v->dep) {
            e->v->dep = u->dep + 1;
            dfs0(e->v);
            st[++teu][0] = u;
        }
    if (teu != u->deu)
        st[++teu][0] = u;
}
int lb[N << 1];
void st_init() {
    static int i, j;
    for (i = 2; i <= teu; ++i)
        lb[i] = lb[i - 1] + ((1 << (lb[i - 1] + 1)) <= i);
    // for (i = 1; i <= teu; ++i)
    //     printf("e %d = %ld\n", i, st[i][0] - g);
    for (j = 1; (1 << j) <= teu; ++j) {
        for (i = 1; i + (1 << j) - 1 <= teu; ++i) {
            if (st[i][j - 1]->dep < st[i + (1 << (j - 1))][j - 1]->dep)
                st[i][j] = st[i][j - 1];
            else
                st[i][j] = st[i + (1 << (j - 1))][j - 1];
        }
    }
}
Node *lca(Node *u, Node *v) {
    static int l, r, t;
    l = u->deu, r = v->deu;
    if (l > r)
        std::swap(l, r);
    t = lb[r - l + 1];
    if (st[l][t]->dep < st[r - (1 << t) + 1][t]->dep)
        return st[l][t];
    else
        return st[r - (1 << t) + 1][t];
}
inline int dis(Node *u, Node *v) {
    return (u != v) ? u->dep + v->dep - lca(u, v)->dep * 2 : 0;
}
Node *rt;
Node *build(Node *u) {
    u = center(u);
    u->done = true;
    for (Edge *e = u->e; e; e = e->e)
        if (!e->v->done)
            darc(u, build(e->v));
    return u;
}
void dfs2(Node *u) {
    u->dh2.insert(0);
    if (u->de) {
        for (Edge *e = u->de; e; e = e->e) {
            dfs2(e->v);
            u->dh2.insert(e->v->dh1.top());
        }
        th.insert(u->dh2.top2());
    }
}
void update(Node *u) {
    static Node *v;
    if (u->ok) {
        u->ok = false;
        --ocnt;
        th.remove(u->dh2.top2());
        u->dh2.remove(0);
        th.insert(u->dh2.top2());
        for (v = u; v->dfa; v = v->dfa) {
            th.remove(v->dfa->dh2.top2());
            v->dfa->dh2.remove(v->dh1.top());
            v->dh1.remove(dis(u, v->dfa));
            v->dfa->dh2.insert(v->dh1.top());
            th.insert(v->dfa->dh2.top2());
        }
        return;
    }
    u->ok = true;
    ++ocnt;
    th.remove(u->dh2.top2());
    u->dh2.insert(0);
    th.insert(u->dh2.top2());
    for (v = u; v->dfa; v = v->dfa) {
        th.remove(v->dfa->dh2.top2());
        v->dfa->dh2.remove(v->dh1.top());
        v->dh1.insert(dis(u, v->dfa));
        v->dfa->dh2.insert(v->dh1.top());
        th.insert(v->dfa->dh2.top2());
    }
}
void init(Node *u) {
    u->ok = true;
    for (Node *v = u; v->dfa; v = v->dfa)
        v->dh1.insert(dis(u, v->dfa)); // printf("%d dh1 <- %d\n", v-g, dis(u,v));
}

int main() {
    static int m, u, v, i;
    static char opt[5];
    scanf("%d", &n);
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        arc(&g[u], &g[v]);
        arc(&g[v], &g[u]);
    }
    g[1].dep = 1;
    dfs0(&g[1]);
    st_init();
    rt = build(&g[1]);
    for (i = 1; i <= n; ++i)
        init(&g[i]);
    ocnt = n;
    dfs2(rt);
    scanf("%d", &m);
    while (m--) {
        scanf("%s", opt);
        if (opt[0] == 'C') {
            scanf("%d", &u);
            update(&g[u]);
        } else
            printf("%d\n", (ocnt <= 1) ? ocnt - 1 : th.top());
    }
    return 0;
}
