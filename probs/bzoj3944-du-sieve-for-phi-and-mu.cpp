#include <cstdio>
#include <cctype>
#include <algorithm>
#include <map>
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
const int K = 1700000;
bool np[K + 2];
int pri[K + 2], mu[K + 2], pcnt;
ll phi[K + 2];
void sieve(const int n) {
    static int i, j;
    static ll v;
    np[0] = np[1] = true;
    mu[1] = phi[1] = 1;
    rep (i, 2, n) {
        if (!np[i]) {
            pri[pcnt++] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (j = 0; j < pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0) {
                mu[v] = 0;
                phi[v] = phi[i] * pri[j];
                break;
            }
            mu[v] = -mu[i];
            phi[v] = phi[i] * (pri[j] - 1);
        }
    }
    rep (i, 2, n) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
}

std::map<int, std::pair<int, ll> > s;
void calc(int n, int &smu, ll &sphi) {
    if (n <= K) {
        smu = mu[n];
        sphi = phi[n];
        return;
    }
    std::map<int, std::pair<int, ll> >::iterator it;
    if ((it = s.find(n)) != s.end()) {
        smu = it->second.first;
        sphi = it->second.second;
        return;
    }
    ll rphi, i, ni;
    int rmu, r;
    smu = 1, sphi = n * ((ll)n + 1) / 2;
    for (i = 2; i <= n; i = ni + 1) {
        r = n / i;
        ni = n / r;
        calc(r, rmu, rphi);
        r = ni - i + 1;
        smu -= r * rmu;
        sphi -= r * rphi;
    }
    s[n] = std::make_pair(smu, sphi);
}

int main() {
    static int t, smu;
    static ll sphi;
    t = io;
    sieve(K);
    while (t--) {
        calc(io, smu, sphi);
        io.print(sphi, false);
        io.pc(' ');
        io.print(smu);
    }

    io.flush(); // ***
    return 0;
}
