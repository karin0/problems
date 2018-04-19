#include <cstdio>
#include <cctype>
#include <algorithm>
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

const int N = 150005, M = 100005;
int n, m, p;
namespace dsu {
    int fa[N];
    void init() {
        static int i;
        re (i, 0, n)
            fa[i] = i;
    }
    int find(const int x) {
        return x == fa[x] ? x : (fa[x] = find(fa[x]));
    }
    inline void unite(const int x, const int y) { 
        fa[find(x)] = find(y);
    }
    inline bool test(const int x, const int y) {
        return find(x) == find(y);
    }
}
struct Edge {
    int u, v, w, f;
    inline bool operator < (const Edge &rhs) const {
        return w < rhs.w || (w == rhs.w && f > rhs.f);
    }
} es[M];
int wd, pcnt, sw;
void check() {
    static int i;
    dsu::init();
    re (i, 0, m)
        if (es[i].f)
            es[i].w += wd;
    std::sort(es, es + m);
    pcnt = sw = 0;
    re (i, 0, m) {
        const Edge &e = es[i];
        if (dsu::test(e.u, e.v))
            continue;
        if (e.f)
            ++pcnt;
        sw += e.w;
        dsu::unite(e.u, e.v);
    }
    sw -= p * wd;
    re (i, 0, m)
        if (es[i].f)
            es[i].w -= wd;
}
int main() {
    static int i, l, r, ans;
    n = io;
    m = io;
    p = io;
    re (i, 0, m) {
        Edge &e = es[i];
        e.u = io;
        e.v = io;
        e.w = io;
        e.f = ((int)io) == 0;
    }
    l = -105;
    r = 105;
    while (l <= r) {
        wd = l + (r - l) / 2;
        check();
        // printf("%d : %d\n", x, ff);
        if (pcnt < p)
            r = wd - 1;
        else // if (pcnt >= p)
            l = wd + 1, ans = sw; // ****
    }
    //wd = r;
    //check();
    io.print(ans);

    io.flush();
    return 0;
}
