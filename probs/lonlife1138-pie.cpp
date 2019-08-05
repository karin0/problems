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
ll gcd(const ll a, const ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll lcm(const ll a, const ll b) {
    return a / gcd(a, b) * b;
}
inline ll lowbit(const ll x) {
    return x & -x;
}
const ll mm = 15, M = 20, S = (1 << 16) + 20, inf = 0x7f7f7f7f;
ll lg[S], coef[M], lc[S], cnt[S];
int main() {
    static ll ks, a[M], i, j, n, m, u = 1 << mm, x;
    static ll ans;
    ks = io;
    rep (i, 1, mm) {
        lg[1 << i] = i;
        coef[i] = (i & 1) ? 1 << (i - 1) : -(1 << (i - 1));
    }
    re (i, 1, u) {
        re (j, 0, mm) if ((i >> j) & 1)
            ++cnt[i];
    }
    while (ks--) {
        n = io, m = io;
        re (i, 0, m)
            a[i] = io;
        u = 1 << m;
        ans = 0;
        re (i, 1, u) {
            x = lowbit(i);
            j = i ^ x;
            if (j) {
                ll t = lcm(a[lg[x]], lc[j]);
                lc[i] = t <= n ? t : inf;
            } else
                lc[i] = a[lg[x]];
            if (lc[i] > n)
                lc[i] = inf;
            else
                ans += (ll)coef[cnt[i]] * ((ll)n / lc[i]);
        }
        io.print(ans);
    }

    io.flush(); // ***
    return 0;
}
