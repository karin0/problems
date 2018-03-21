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
const int N = 100003, p = 100003;
ll inv[N], f[N], ans;
std::vector<int> divs[N];
int main() {
    static int n, k, x, i, j;
    static bool a[N];
    n = io;
    k = io;
    rep (i, 1, n)
        a[i] = (int)io;
    rep (i, 1, n)
        for (j = i; j <= n; j += i)
            divs[j].push_back(i);
    per (i, n, 1) if (a[i]) {
        for (std::vector<int>::iterator it = divs[i].begin(); it != divs[i].end(); ++it)
            a[*it] ^= 1;
        ++x;
    }
    if (k < x) {
        inv[1] = 1;
        rep (i, 2, n)
            inv[i] = (p - p / i) * inv[p % i] % p;
        f[n] = 1;
        pe (i, n - 1, k)
            f[i] = (n + (n - i) * f[i + 1]) % p * inv[i] % p;
        ans = k;
        rep (i, k + 1, x) {
            ans += f[i];
            if (ans >= p)
                ans -= p;
        }
    } else
        ans = x;
    rep (i, 2, n)
        ans = ans * i % p;
    io.print(ans);
    io.flush(); // ***
    return 0;
}
