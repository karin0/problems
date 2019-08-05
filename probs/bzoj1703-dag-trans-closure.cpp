#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
#include <bitset>
#include <vector>
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

const int N = 1003, M = 10003;
int deg[N];
std::vector<int> g[N];
std::bitset<1001> d[N];
std::queue<int> q;

int main() { // answer should be at the worst case
    static int n, m, i, ans, u, v;
    n = io;
    m = io;
    rep (i, 1, m) {
        u = io;
        v = io;
        g[u].push_back(v);
        ++deg[v];
    }
    rep (i, 1, n)
        if (!deg[i])
            q.push(i);
    while (!q.empty()) {
        static std::vector<int>::iterator it, ed;
        std::bitset<1001> &du = d[u];
        u = q.front();
        q.pop();
        ans += du.count();
        ed = g[u].end();
        for (it = g[u].begin(); it != ed; ++it) {
            v = *it;
            d[v] |= du;   // use |=, not =  ****************
            d[v].set(u);
            if (--deg[v] == 0)
                q.push(v);
        }
    }
    io.print(((n * (n - 1)) >> 1) - ans);

    io.flush();
    return 0;
}
