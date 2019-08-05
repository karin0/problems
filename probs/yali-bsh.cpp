#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <queue>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; // return s == t ? -1 : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
        *st++ = 0;
    }
    template <class T>
    operator T() {
        static T x;
        static char c;
        static bool neg;
        for (c = gc(); c != '-' && !isdigit(c); c = gc());
        if (c == '-')
            neg = true, c = gc();
        else
            neg = false;
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return neg ? -x : x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(b, 1, L, stdout), p = b;
        *p++ = c;
    }
    template<class T>
    void print(T x, const bool nl = true) {
        static char c[30], *q;
        static T y;
        if (x == 0)
            pc('0');
        else {
            if (x < 0)
                pc('-'), x = -x;
            for (q = c; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != c)
                pc(*--q);
        }
        if (nl)
            pc('\n');
    }
    void ps(const char *st, const bool nl = true) {
        while (*st)
            pc(*st++);
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 52005, E = 2 * N, Q = 2 * N, inf = 0x3f3f3f3f;
int n, len;
bool inc[N];
std::vector<int> sec, sec2, tmp;
std::vector<int> adj[N];
struct Query {
    int u, v, *ans;
} qwq[Q];
inline int prev(const int u) {
    return u == 1 ? n : (u - 1);
}
inline int next(const int u) {
    return u == n ? 1 : (u + 1);
}
inline int mdis(const int s, const int t) {
    return s <= t ? std::max(t - s, n + s - t) : std::max(s - t, n - s + t);
}
int u_diag, v_diag;
inline bool right(const int u) {
    return u_diag < u && u < v_diag;
}
inline void upd(int &x, const int v) {
    x = std::min(x, v);
}
void find_mid() {
    static int maxd, d;
    static std::vector<int>::iterator it, o;
    maxd = 0;
    for (o = sec.begin(); o != sec.end(); ++o)
        for (it = adj[*o].begin(); it != adj[*o].end(); ++it)
            if (inc[*it] && (d = mdis(*o, *it)) > maxd)
                maxd = d, u_diag = *o, v_diag = *it;
    if (u_diag > v_diag)
        std::swap(u_diag, v_diag);
}
int dis[N];
void bfs(const int s) {
    static int u, v, du;
    static std::queue<int> q;
    static std::vector<int>::iterator o;
    for (o = sec.begin(); o != sec.end(); ++o)
        dis[*o] = -1;
    dis[s] = 0;
    q.push(s);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        du = dis[u];
        if (inc[v = prev(u)] && dis[v] == -1)
            dis[v] = du + 1, q.push(v);
        if (inc[v = next(u)] && dis[v] == -1)
            dis[v] = du + 1, q.push(v);
        for (o = adj[u].begin(); o != adj[u].end(); ++o)
            if (inc[v = *o] && dis[v] == -1)
                dis[v] = du + 1, q.push(v);
    }
}
void solve(Query *const ql, Query *const qr) {
    if (len < 3 || ql > qr) {
        sec.clear();
        return;
    }
    if (len == 3) {
        for (Query *q = ql; q <= qr; ++q)
            *q->ans = 1;
        sec.clear();
        return;
    }
    find_mid();
    bfs(u_diag);
    Query *q, *tl = ql, *tr = qr;
    for (q = ql; q <= qr; ++q)
        upd(*q->ans, dis[q->u] + dis[q->v]);
    bfs(v_diag);
    for (q = ql; q <= qr; ++q)
        upd(*q->ans, dis[q->u] + dis[q->v]);
    bool ru, rv;
    int u, cnt2 = 0;
    for (q = ql; q <= tr; ++q) {
        ru = right(q->u), rv = right(q->v);
        if (ru && rv)
            std::swap(*tr--, *q--);
        else if (!ru && !rv)
            *tl++ = *q;
    }
    tmp = sec;
    sec.clear();
    std::vector<int>::iterator o;
    for (o = tmp.begin(); o != tmp.end(); ++o) {
        if (u == u_diag || u == v_diag)
            sec.push_back(u), sec2.push_back(u);
        else if (right(u = *o))
            sec2.push_back(u), inc[u] = false, --len, ++cnt2;
        else
            sec.push_back(u);
    }
    tmp.clear();
    solve(ql, tl - 1);
    while (cnt2--) {
        u = sec2.back();
        sec.push_back(u);
        inc[u] = true;
        ++len;
        sec2.pop_back();
    }
    solve(tr + 1, qr);
    for (o = sec.begin(); o != sec.end(); ++o)
        inc[*o] = false;
    sec.clear();
    len = 0;
}
int main() {
    static int m, p, u, v, i, ans[Q];
    n = io;
    rep (i, 4, n) {
        u = io, v = io;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    m = io;
    re (i, 0, m) {
        u = io, v = io;
        if (u == v)
            ans[i] = 0;
        else if (std::abs(u - v) == 1)
            ans[i] = 1;
        else
            qwq[p++] = Query{u, v, &(ans[i] = inf)};
    }
    len = n;
    rep (i, 1, n)
        sec.push_back(i), inc[i] = true;
    solve(qwq, qwq + p - 1);
    re (i, 0, m)
        io.print(ans[i]);

    io.flush(); // ***
    return 0;
}
