#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define SAY(x) std::cerr << #x " = " << x << std::endl
#else
    #define SAY(x) 0
#endif

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
    void print(T x, const char end = '\n') {
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
        if (end)
            pc(end);
    }
    void ps(const char *st, const char end = '\n') {
        while (*st)
            pc(*st++);
        if (end)
            pc(end);
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;
using std::abs;
typedef long long ll;
ll g;
void exgcd(ll a, ll b, ll &x, ll &y) {
    b ? (exgcd(b, a % b, y, x), y -= x * (a / b)) : (g = a, x = 1, y = 0);
}
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
void ans(ll x = -1, ll y = -1) {
    if (x == -1 || y == -1) {
        io.ps("-1");
    } else {
        io.print(x, ' ');
        io.print(y);
    }
    io.flush();
    exit(0);
}
ll n, m, X0, Y0, vx, vy;
int main() {
    static ll p, q, a, b, A, B, rh, n1, m1;
    n = io;
    m = io;
    X0 = io;
    Y0 = io;
    vx = io;
    vy = io;
    if (vx == 0) {
        if (X0 == 0 || X0 == n)
            ans(X0, vy == 1 ? m : 0);
        ans();
    }
    if (vy == 0) {
        if (Y0 == 0 || Y0 == m)
            ans(vx == 1 ? n : 0, Y0);
        ans();
    }
    p = vx == 1 ? n - X0 : X0;
    q = vy == 1 ? m - Y0 : Y0;
    rh = q - p;
    if (rh == 0) {
        a = 0, b = 0;
        if (vx == 1)
            ++a;
        if (vy == 1)
            ++b;   // ******** this also need to be done here.
        ans((a & 1ll) * n, (b & 1ll) * m);
    }
    exgcd(n, m, A, B); // A = a, B = -b >= 0
    if (abs(rh) % g != 0)
        ans();
    n1 = n / g;
    m1 = m / g;
    a = A * (rh / g);
    b = -B * (rh / g);
    a = (a % m1 + m1) % m1;   // ***** use m1 = m / gcd(n, m) to construct general solutions
    b = (a * n - rh) / m;
	if (b < 0) {
        SAY(a);
        SAY(b);
        SAY("that is bad");
		b = (b % n1 + n1) % n1;
		a = (b * m + rh) / n;
	}
	SAY(a); SAY(b); SAY(rh); SAY(p); SAY(q); SAY(p + a * n);
    SAY(q + b * m); SAY("SOLVED");
    if (vx == 1)
        ++a;
    if (vy == 1)
        ++b;
    ans((a & 1ll) * n, (b & 1ll) * m);
    io.flush();
    return 0;
}
