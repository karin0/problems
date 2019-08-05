#include <cstdio>
#include <cmath>
#include <climits>
#include <algorithm>

const int N = 50003, M = 100003, Q = N;
inline int max(const int a, const int b, const int c) {
    return std::max(a, std::max(b, c));
}
struct UFS {
    int fa[N], rk[N], ma[N], mb[N], ssiz;
    struct Oper {
        int *pos, old;
    } sta[M << 3];
    void init(const int n) {
        ssiz = 0;
        for (int i = 0; i < n; ++i)
            fa[i] = i, rk[i] = 0, ma[i] = mb[i] = -1;
    }
    void mod(int &pos, const int x) {
        sta[ssiz++] = Oper{&pos, pos};
        pos = x;
    }
    void restore(const int s) {
        while (ssiz > s)
            --ssiz, *sta[ssiz].pos = sta[ssiz].old;
    }
    /*
    int find(int x) const {
        while (x != fa[x])
            x = fa[x];
        return x;
    }*/
    int find(const int x) const {
        return x == fa[x] ? x : find(fa[x]);
    }
    void unite(int x, int y, const int a, const int b) {
        x = find(x), y = find(y);
        if (x != y) {
            if (rk[x] == rk[y])
                mod(rk[y], rk[y] + 1);
            else if (rk[x] > rk[y])
                std::swap(x, y);
            mod(fa[x], y);
        }
        mod(ma[y], max(ma[x], ma[y], a));
        mod(mb[y], max(mb[x], mb[y], b));
    }
    bool test(int x, int y, const int a, const int b) const {
        x = find(x), y = find(y);
        return x == y && ma[x] == a && mb[x] == b;
    }
} ufs;
struct Edge {
    int u, v, a, b;
} es[M];
struct Query {
    int u, v, a, b;
    bool *ans;
} qwq[Q];
template <class T>
bool cmp_by_a(const T &a, const T &b) {
    return a.a < b.a;
}
template <class T>
bool cmp_by_b(const T &a, const T &b) {
    return a.b < b.b;
}
int main() {
    static int n, m, p, i, j, k, bsiz, ql, qr, el, er, br, mk;
    static bool ans[Q];
    scanf("%d%d", &n, &m);
    bsiz = floor(sqrt(7 * m) + 0.5);
    for (i = 0; i < m; ++i) {
        Edge &e = es[i];
        scanf("%d%d%d%d", &e.u, &e.v, &e.a, &e.b);
        --e.u, --e.v;
    }
    scanf("%d", &p);
    for (i = 0; i < p; ++i) {
        Query &q = qwq[i];
        scanf("%d%d%d%d", &q.u, &q.v, &q.a, &q.b);
        --q.u, --q.v;
        q.ans = &ans[i];
    }
    std::sort(es, es + m, cmp_by_a<Edge>);
    std::sort(qwq, qwq + p, cmp_by_a<Query>);
    es[m].a = INT_MAX;
    for (i = qr = 0; i < m && qr < p; i += bsiz) {
        br = std::min(m, i + bsiz);
        for (ql = qr; qr < p && qwq[qr].a < es[br].a; ++qr);
        std::sort(es, es + i, cmp_by_b<Edge>);
        std::sort(qwq + ql, qwq + qr, cmp_by_b<Query>);
        ufs.init(n);
        for (el = 0, er = i, j = ql; j < qr; ++j) {
            Query &q = qwq[j];
            for (; el < er && es[el].b <= q.b; ++el) {
                Edge &e = es[el];
                ufs.unite(e.u, e.v, e.a, e.b);
            }
            mk = ufs.ssiz;
            for (k = i; k < br; ++k) {
                Edge &e = es[k];
                if (e.a <= q.a && e.b <= q.b)
                    ufs.unite(e.u, e.v, e.a, e.b);
            }
            *q.ans = ufs.test(q.u, q.v, q.a, q.b);
            ufs.restore(mk);
        }
    }
    for (i = 0; i < p; ++i)
        puts(ans[i] ? "Yes" : "No");

    return 0;
}
