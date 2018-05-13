#include <cstdio>
#include <cctype>
#include <algorithm>
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
        return *s++; // return s == t ? EOF : *s++;
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
            fwrite(p = b, 1, L, stdout);
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

const int N = 100002;
struct Edge {
    int v;
    Edge *e;
} pool[N * 100], *curr = pool, *g[N * 2];
void arc(int u, int v) {
    g[u] = new (curr++) Edge{v, g[u]};
}
int n, nn, k, a[N * 2], b[N * 2], d[N * 2];
std::queue<int> q;
std::pair<int, int> l[N], *p;
int main() {
    static int i, u, v, nd;
    n = io;
    k = io;
    nn = n + n;
    rep (i, 1, n) {
        a[i] = io;
        b[i] = io;
        if (b[i] == 0)
            q.push(i), d[i] = 1;
    }
    rep (i, n + 1, nn) {
        a[i] = io;
        b[i] = io;
        if (a[i] == 0)
            q.push(i), d[i] = 1;
    }
    rep (i, 1, n)
        l[i] = std::make_pair(b[n + i], n + i);
    std::sort(l + 1, l + n + 1);
    rep (i, 1, n) {
        p = std::lower_bound(l + 1, l + n + 1, std::make_pair(b[i], 0));
        while (p <= l + n && b[i] <= p->first && p->first <= b[i] + k)
            arc((p++)->second, i);
    }
    rep (i, 1, n)
        l[i] = std::make_pair(a[i], i);
    std::sort(l + 1, l + n + 1);
    rep (i, n + 1, nn) {
        p = std::lower_bound(l + 1, l + n + 1, std::make_pair(a[i], 0));
        while (p <= l + n && a[i] <= p->first && p->first <= a[i] + k)
            arc((p++)->second, i);
    }

    static Edge *e;
    while (!q.empty()) {
        u = q.front();
        q.pop();
        nd = d[u] + 1;
        for (e = g[u]; e; e = e->e) if (d[v = e->v] == 0) {
            d[v] = nd;
            q.push(v);
        }
    }
    rep (i, 1, n)
        io.print(d[i] ? d[i] : -1);

    io.flush();
    return 0;
}
