#include <cstdio>
#include <cstring>
#include <cmath>
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
        return s == t ? -1 : *s++;
    }
    void gs(char *st) {
        static char c;
        for (c = gc(); !isgraph(c); c = gc());
        *st++ = c;
        for (c = gc(); isgraph(c); c = gc())
            *st++ = c;
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
        if (neg)
            x = -x;
        return x;
    }
    inline void pc(const char c) {
        if (p == b + L)
            fwrite(b, 1, L, stdout), p = b;
        *p++ = c;
    }
    template<class T>
    void print(T x) {
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
    }
    void puts(const char *st) {
        while (*st)
            pc(*st++);
    }
    inline void flush() {
        fwrite(b, 1, p - b, stdout);
    }
} io;

typedef long long ll;
const int N = 100333;
int bs, dv[N];
struct Query {
    int l, r;
    ll *ans;
    bool operator < (const Query &rhs) const {
        return dv[l] < dv[rhs.l] || (dv[l] == dv[rhs.l] && r < rhs.r);
    }
} qwq[N];
int main() {
    static int p, n, m, a[N], i, h[N], *end, c[N], l, r, g[N];
    static ll ans[N], res, t, f[N];
    static char s[N];
    p = io;
    if (p == 2) {
        io.gs(s + 1);
        m = io;
        for (i = 1; s[i]; ++i) {
            f[i] = f[i - 1];
            g[i] = g[i - 1];
            if (((s[i] - '0') & 1) == 0)
                f[i] += i, ++g[i];
        }
        re (i, 0, m) {
            l = (int)io - 1;
            r = (int)io;
            io.print(f[r] - f[l] - (ll)l * (g[r] - g[l]));
            io.pc('\n');
        }
        io.flush();
        return 0;
    } else if (p == 5) {
        io.gs(s + 1);
        m = io;
        for (i = 1; s[i]; ++i) {
            f[i] = f[i - 1];
            g[i] = g[i - 1];
            if (s[i] == '5' || s[i] == '0')
                f[i] += i, ++g[i];
        }
        re (i, 0, m) {
            l = (int)io - 1;
            r = (int)io;
            io.print(f[r] - f[l] - (ll)l * (g[r] - g[l]));
            io.pc('\n');
        }
        io.flush();
        return 0;
    }
    io.gs(s);
    m = io;
    a[0] = 0;
    for (i = 0; s[i]; ++i)
        a[i + 1] = (a[i] * 10ll + (s[i] - '0')) % p;
    // we have to make index from 1, or a[-1] could be accessed when q.l == 1
    n = i;
    for (i = n, t = 1; i >= 1; --i, t = t * 10 % p)
        h[i] = (a[i] = t * a[i] % p);
    std::sort(h, h + n + 1);
    end = std::unique(h, h + n + 1);
    rep (i, 1, n)
        a[i] = std::lower_bound(h, end, a[i]) - h;
    re (i, 0, m) {
        Query &q = qwq[i];
        q.l = (int)io - 1;
        q.r = (int)io;
        q.ans = &ans[i];
    }
    r = bs = sqrt(3.0 * n * n / m);
    re (i, 1, n) {
        if (i >= r)
            dv[i] = dv[i - 1] + 1, r += bs;
        else
            dv[i] = dv[i - 1];
    }
    std::sort(qwq, qwq + m);
    const Query &q = qwq[0];
    l = q.l, r = q.r;
    rep (i, l, r)
        res += c[a[i]], ++c[a[i]];
    *q.ans = res;
    re (i, 1, m) {
        const Query &q = qwq[i];
        while (l < q.l)
            c[a[l]]--, res -= c[a[l]], ++l;
        while (q.r < r)
            c[a[r]]--, res -= c[a[r]], --r;
        while (q.l < l)
            --l, res += c[a[l]], ++c[a[l]];
        while (r < q.r)
            ++r, res += c[a[r]], ++c[a[r]];
        *q.ans = res;
    }
    re (i, 0, m)
        io.print(ans[i]), io.pc('\n');

    io.flush();
    return 0;
}
