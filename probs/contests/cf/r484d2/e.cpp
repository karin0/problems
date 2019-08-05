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
int g;
void extgcd(int a, int b, int &x, int &y) {
    b ? (extgcd(b, a % b, y, x), y -= x * (a / b)) : (g = a, x = 1, y = 0);
}
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}
void ans(int x = -1, int y = -1) {
    if (x == -1 || y == -1) {
        io.ps("-1");
    } else {
        io.print(x, ' ');
        io.print(y);
    }
}
int n, m, X0, Y0, vx, vy;
void anss(int p, int q) {
    ans((p & 1) * n, (q & 1) * m);
}
int main() {
    static int k, b, p, q;
    n = io;
    m = io;
    X0 = io;
    Y0 = io;
    vx = io;
    vy = io;
    if (vx == 0) {
        if (X0 == 0 || X0 == n)
            ans(X0, vy == 1 ? m : 0);
        else
            ans();
    } else if (vy == 0) {
        if (Y0 == 0 || Y0 == m)
            ans(vx == 1 ? n : 0, Y0);
        else
            ans();
    } else {
        //puts("damn");
        k = vy / vx;
        b = Y0 - k * X0;
        extgcd(m, n, q, p);
        if (abs(b) % g != 0) {
            ans(); // puts("no sol");
        } else {
            b /= g;
            m /= g;
            n /= g;
            q = ((q % n) + n) % n;
            p = (1 - q * m) / n;
            q *= g;
            p *= g;
            anss(abs(p), abs(q));
            /*
            if (k == 1) {
                if (n == 1)
                    ans(n, 0);
                else if (m == 1)
                    ans(0, m);
                else
                    ans();
            } else {
                exgcd(m, n, q, p);
            }*/
        }
    }

    io.flush();
    return 0;
}
