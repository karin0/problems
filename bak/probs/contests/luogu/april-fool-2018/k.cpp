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

const int N = 600;
struct Vec {
    double x, y, z;
    Vec(double i=0, double j=0, double k=0) : x(i), y(j), z(k) {}
    Vec operator * (const int k) const {
        return Vec(x * k, y * k, z * k);
    }
    Vec operator / (const int k) const {
        return Vec(x / k, y / k, z / k);
    }
    Vec operator + (const Vec b) const {
        return Vec(x + b.x, y + b.y, z + b.z);
    }
} v[N], p[N];
int n, mass[N], sm;
Vec mean(const Vec z[]) {
    Vec a = Vec(0, 0, 0);
    int i;
    rep (i, 1, n)
        a = a + z[i] * mass[i];
    return a / sm;
}
int main() {
    int t, i, x, y, z;
    n = io;
    t = io;
    rep (i, 1, n) {
        mass[i] = io;
        sm += mass[i];
        x = io;
        x = io;
        y = io;
        z = io;
        p[i] = Vec(x, y, z);
        x = io;
        y = io;
        z = io;
        v[i] = Vec(x, y, z);
    }
    Vec mx = mean(p), mv = mean(v);
    Vec h = mx + mv * t;
    printf("%f %f %f\n", h.x, h.y, h.z);

    return 0;
}
