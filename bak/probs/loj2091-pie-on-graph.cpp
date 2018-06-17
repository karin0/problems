#include <cstdio>
#include <cctype>
#include <algorithm>
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

typedef long long ll;
const int N = 19;
int cnt, vtx[N], s;
ll f[N][N];
std::vector<int> tr[N], g[N];
#define tadj(u) for (std::vector<int>::iterator ti = tr[u].begin(); ti != tr[u].end(); ++ti)
#define gadj(u) for (std::vector<int>::iterator it = g[u].begin(); it != g[u].end(); ++it)

void dfs(const int u, const int fa) {
    static ll *fp, *fu, r;
    static int i, v, j;
    tadj (u) if (*ti != fa)
        dfs(*ti, u);
    fu = f[u];
    re (i, 0, cnt) {
        ll &ff = fu[v = vtx[i]];
        ff = 1;
        tadj (u) if (*ti != fa) {
            r = 0;
            fp = f[*ti];
            gadj (v) if ((s >> *it) & 1)
                r += fp[*it];
            ff *= r;
        }
    }
}
int main() {
    static int n, m, u, v, i, rt;
    static ll ans, r, *fr;
    n = io, m = io;
    re (i, 0, m) {
        u = io, v = io;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    re (i, 1, n) {
        u = io, v = io;
        --u, --v;
        tr[u].push_back(v);
        tr[v].push_back(u);
    }
    u = 1 << n;
    re (s, 1, u) {
        cnt = 0;
        re (i, 0, n) if ((s >> i) & 1)
            vtx[cnt++] = i;
        dfs(rt = vtx[0], -1);
        r = 0;
        fr = f[rt];
        re (i, 0, cnt)
            r += fr[vtx[i]];
        if ((n - cnt) & 1)
            ans -= r;
        else
            ans += r;
    }
    io.print(ans);

    io.flush(); // ***
    return 0;
}
