#include <cstdio>
#include <algorithm>
#include <queue>

const int N = 100005;
struct Heap {
    std::priority_queue<int> q, d;
    inline void clean() {
        while (!q.empty() && !d.empty() && q.top() == d.top())
            q.pop(), d.pop();
    }
    inline void insert(int x) {
        if (x >= 0)
            q.push(x);
    }
    inline void remove(int x) {
        if (x >= 0)
            d.push(x);
    }
    inline int size() {
        return q.size() - d.size();
    }
    inline int top() {
        clean();
        return size() ? q.top() : -1234567;
    }
    inline void pop() {
        clean();
        if (!q.empty())
            q.pop();
    }
    inline int top2() {
        static int t, tt;
        t = top();
        if (t < 0)
            return -1234567;
        // pop();
        remove(t);
        tt = top();
        if (tt < 0)
            return -1234567;
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
void dfs2(Node *u, Node *f) {
    for (Edge *e = u->de; e; e = e->e)
        if (e->v != f) {
            e->v->dfa = u;
            dfs2(e->v, u);
        }
}
Node *st[N << 1][20];
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
int lb[N];
void st_init() {
    static int i, j;
    lb[1] = 0;
    for (i = 1; i <= teu; ++i)
        lb[i] = lb[i - 1] + ((1 << (lb[i - 1] + 1)) <= i);
    // for (i = 1; i <= teu; ++i)
    //     printf("e %d = %ld\n", i, st[i][0] - g);
    for (j = 1; (1 << j) <= teu; ++j) {
        for (i = 1; i + (1 << j) - 1 <= teu; ++i) {
            printf("Making %d, %d\n", i, j);
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
    if (u == v)
        return 0;
    return u->dep + v->dep - lca(u, v)->dep * 2;
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
void update(Node *u) {
    static int d, t;
    static Node *v;
    if (u->ok) {
        printf("Opening %d\n", u - g);
        u->ok = false;
        --ocnt;
        for (v = u; v; v = v->dfa) {
            d = dis(u, v);
            if (v->dfa) {
                t = dis(v, v->dfa);
                th.remove(v->dfa->dh2.top2());
                v->dfa->dh2.remove(v->dh1.top() + t);
                v->dh1.remove(d);
                v->dfa->dh2.insert(v->dh1.top() + t);
                th.insert(v->dfa->dh2.top2());
            } else
                v->dh1.remove(d);
        }
        return;
    }
    u->ok = true;
    printf("Closing %d\n", u - g);
    ++ocnt;
    for (v = u; v; v = v->dfa) {
        d = dis(u, v);
        printf("dis(%d, %d) = %d\n", u - g, v - g, d);
        if (v->dfa) {
            t = dis(v, v->dfa);
            printf("t (dis(%d to fa %d)) is %d\n", v - g, v->dfa - g, t);
            th.remove(v->dfa->dh2.top2());
            v->dfa->dh2.remove(v->dh1.top() + t);
            v->dh1.insert(d);
            v->dfa->dh2.insert(v->dh1.top() + t);
            th.insert(v->dfa->dh2.top2());
        } else
            v->dh1.insert(d);
    }
}
inline int query() {
    return th.top();
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
    dfs2(rt, NULL);
    for (i = 1; i <= n; ++i)
        update(&g[i]);
    scanf("%d", &m);
    while (m--) {
        for (i = 1; i <= n; ++i)
            printf("%d's q1 siz = %d, q2 siz = %d\n", i, g[i].dh1.size(), g[i].dh2.size());
        printf("ocnt is %d\n", ocnt);
        scanf("%s", opt);
        if (opt[0] == 'C') {
            scanf("%d", &u);
            update(&g[u]);
        } else
            printf("%d\n", (ocnt <= 1) ? ocnt - 1 : query());
    }
}
