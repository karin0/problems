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
void extgcd(ll a, ll b, ll &x, ll &y) {
    b ? (extgcd(b, a % b, y, x), y -= x * (a / b)) : (g = a, x = 1, y = 0);
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
ll n, m, X0, Y0, vx, vy, N, M;
void anss(ll p, ll q) {
    SAY(p);
    SAY(q);
    ans((std::abs(p) & 1) * N, (std::abs(q) & 1) * M);
}
int main() {
    static ll k, b, p, q, s;
    N = n = io;
    M = m = io;
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
        SAY(m); SAY(n); SAY(k); SAY(b);
        extgcd(m, n, q, p);
        // Solve qm + pn = 1
        // Qm - kPn = b
        // Q = bq, P = -bp / k = -bkp
        SAY(q); SAY(p);
        if (b == 0) {
            // Qm = kPn, P / Q = m / kn  // ******** or P = Q = 0 !
            m /= g;
            n /= g;
            if (vy == 1)
                anss(m, n);
            else
                ans(0, 0);
            SAY("iiokoio");
        } else if (abs(b) % g != 0) {
            ans();// puts("no sol");
        } else {
            b /= g;
            m /= g;
            n /= g;
            if (b < 0) {
                b = -b;
                p = -p;
                q = -q;
                s = -1;
            } else
                s = 1;
            // then qm + pn = s;
            SAY(p);
            SAY(q);
            SAY(s);
            SAY(q*m + p*n);
            if (vy == 1) {
                q = (q % n + n) % n; // min >0 q
                if (!q)
                    q += n;
                p = (s - q * m) / n;   // ******** here could boooom int!
            } else /*if (vx == 1 && vy == -1)*/ {
                q = (q % n + n) % n;
                if (q > 0)
                    q -= n; // max <=0 q
                p = (s - q * m) / n;
            }
            SAY(p);
            SAY(q);
            SAY(q*m + p*n);
            SAY("make answer");
            SAY(p);
            SAY(q);
            SAY(q*m + p*n);
            p = std::abs(p) & 1;
            q = std::abs(q) & 1;
            anss(p * b, q * b);
            /*
            p = (p % m + m) % m;
            q = (1 - p * n) / m;
            if (vx > 0) {
                anss(-p * b, q * b);
            } else {
                if (p < 0) {
                    p = (p % m + m) % m;
                    q = (1 - p * n) / m;
                }
                anss(p * b, q * b);
            }*/
        }
    }

    io.flush();
    return 0;
}
