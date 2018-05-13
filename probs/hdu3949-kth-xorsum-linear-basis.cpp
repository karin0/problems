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

typedef long long ll;
const int w = 59;
template <class T>
inline bool bit(const T x, const int k) {
    return (x >> k) & 1;
}
namespace basis {
    ll b[w], v[w + 3];
    int vcnt, i;
    bool zero;
    void insert(ll x) {
        static int j;
        // printf("Ins %lld\n", x);
        for (i = w; i >= 0; --i) {
            if (!x)
                return;
            if (!bit(x, i))
                continue;
            if (b[i])
                x ^= b[i];
            else {
                for (j = 0; j < i; ++j)
                    if (bit(x, j))
                        x ^= b[j];
                for (j = i + 1; j <= w; ++j)
                    if (bit(b[j], i))
                        b[j] ^= x;
                b[i] = x;
                return;
            }
        }
    }
    void init(const int n) {
        rep (i, 0, w) if (b[i])
            v[vcnt++] = b[i];
        zero = n > vcnt;
    }
    void clear() {
        rep (i, 0, w)
            b[i] = 0;
        vcnt = 0;
    }
    ll query(ll k) {
        static ll res;
        if (zero) {
            if (k == 1)
                return 0;
            --k;
        }
        if (k >= (1ll << vcnt))   // ****
            return -1;
        for (res = 0, i = 0; i < vcnt; ++i) if (bit(k, i))
            res ^= v[i];
        return res;
    }
}
int main() {
    static int kc, ks, n;
    ks = io;
    rep (kc, 1, ks) {
        static int i, m;
        n = io;
        // printf("n = %d\n", n);
        rep (i, 1, n)
            basis::insert((ll)io);
        basis::init(n);
        io.ps("Case #", false);
        io.print(kc, false);
        io.pc(':');
        io.pc('\n');
        m = io;
        // printf("m = %d\n", m);
        rep (i, 1, m)
            io.print(basis::query((ll)io));
        if (kc < ks)
            basis::clear();
    }

    io.flush();
    return 0;
}
