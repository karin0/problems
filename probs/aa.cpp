#include <cstdio>
#include <vector>
#include <algorithm>
const int MAXN = 100005;
const int CHAR_SET = 10;
struct SuffixAutomaton {
    struct Node {
        Node *c[CHAR_SET], *next;
        int max;
        Node(int max = 0) : max(max), c(), next(NULL) {}
        int getMin() {
            return next->max + 1;
        }
    } *start, _pool[MAXN * 40], *_curr;
    SuffixAutomaton() {
        init();
    }
    void init() {
        _curr = _pool;
        start = new (_curr++) Node();
    }
    Node *extend(Node *v, int c) {
        if (v->c[c] && v->c[c]->max == v->max + 1) return v->c[c];
        Node *u = new (_curr++) Node(v->max + 1);
        while (v && !v->c[c]) {
            v->c[c] = u;
            v = v->next;
        }
        if (!v) {
            u->next = start;
        } else if (v->c[c]->max == v->max + 1) {
            u->next = v->c[c];
        } else {
            Node *n = new (_curr++) Node(v->max + 1), *o = v->c[c];
            std::copy(o->c, o->c + CHAR_SET, n->c);
            n->next = o->next;
            o->next = u->next = n;
            for (; v && v->c[c] == o; v = v->next) v->c[c] = n;
        }
        return u;
    }
    long long calc() {
        long long res = 0;
        for (Node *p = _pool + 1; p != _curr; p++) res += p->max - p->getMin() + 1;
        return res;
    }
} sam;
struct Edge;
struct Node {
    Edge *e;
    int c, deg;
} N[MAXN];
struct Edge {
    Node *u, *v;
    Edge *next;
    Edge() {}
    Edge(Node *u, Node *v) : u(u), v(v), next(u->e) {}
} _pool[MAXN << 1], *_curr = _pool;
void addEdge(int u, int v) {
    N[u].e = new (_curr++) Edge(&N[u], &N[v]);
    N[v].e = new (_curr++) Edge(&N[v], &N[u]);
    N[u].deg++;
    N[v].deg++;
}
void dfs(Node *u, Node *fa, SuffixAutomaton::Node *last) {
    SuffixAutomaton::Node *v = sam.extend(last, u->c);
    for (Edge *e = u->e; e; e = e->next) if (e->v != fa) dfs(e->v, u, v);
}
int main() {
    int n;
    scanf("%d %*d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &N[i].c);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);
    }
    for (int i = 1; i <= n; i++) if (N[i].deg == 1) dfs(&N[i], NULL, sam.start);
    printf("%lld\n", sam.calc());
    return 0;
}
