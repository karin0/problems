#include <akari>
#include <queue>

IO<1000000, 1000000> io;

cint R = 4005, C = 6005, V = R * C / 10, inf = 0x3f3f3f3f;

int n, len[R];
char a[R][C];
inline int get(int i, int j) {
    if (i >= 1 && i <= n && j >= 1 && j <= len[i])
        return a[i][j];
    return 0;
}
inline bool is_center(int i, int j) {
    return get(i - 2, j - 2) == '+' &&
           get(i - 2, j + 2) == '+' &&
           get(i, j - 4) == '+' &&
           get(i, j + 4) == '+' &&
           get(i + 2, j - 2) == '+' &&
           get(i + 2, j + 2) == '+';
}

struct Node {
    int x, y, d;
    struct Edge *e;
} g[V], *id[R][C], *ns, *nt;
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *v, Edge *e) : v(v), e(e) {}
} pool[V * 6], *curr;
inline void arc(Node *u, Node *v) {
    u->e = new (curr++) Edge(v, u->e);
    v->e = new (curr++) Edge(u, v->e);
}

struct S {
    ll d;
    Node *u;
    S() {}
    S(ll d, Node *u) : d(d), u(u) {}
    bool operator < (const S &rhs) const {
        return d > rhs.d;
    }
};
std::priority_queue<S> q;
inline int solve() {
    q.push(S(ns->d = 1, ns));
    while (!q.empty()) {
        Node *u = q.top().u;
        q.pop();
        int t = u->d + 1;
        for (Edge *e = u->e; e; e = e->e)
            if (e->v->d > t)
                q.push(S(e->v->d = t, e->v));
    }
    return nt->d < inf ? nt->d : -1;
}

cint de[3][4] = {
    {-1, -3, -2, -6},
    {-1,  3, -2,  6},
    {-2,  0, -4,  0}
};

int main() {
    int T;
    io >> T;
    while (true) {
        curr = pool;
        int r, c;
        io >> r >> c;
        n = (r << 2) + 3;
        rep (i, 1, n)
            len[i] = io.gl(a[i] + 1) - (a[i] + 1);
        int cnt = 0;
        rep (i, 1, n) rep (j, 1, len[i]) if (is_center(i, j)) {
            Node *u = id[i][j] = &g[++cnt];
            u->x = i;
            u->y = j;
            u->d = inf;
            if (!ns && a[i][j] == 'S')
                ns = u;
            else if (!nt && a[i][j] == 'T')
                nt = u;
        }
        rep (k, 1, cnt) {
            int x = g[k].x, y = g[k].y;
            Node *u = id[x][y];
            re (i, 0, 3) {
                cint *d = de[i];
                if (a[x + d[0]][y + d[1]] == ' ')
                    arc(u, id[x + d[2]][y + d[3]]);
            }
        }
        io << solve() daze;
        if (--T) {
            ns = nt = NULL;
            rep (i, 1, cnt)
                g[i].e = NULL;
        } else
            return 0;        
    }
}