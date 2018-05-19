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
const double eps = 1e-7;

int dcmp(const double x) {
    return fabs(x) <= eps ? 0 : (x > 0 ? 1 : -1);
}
struct Vec {
    double x, y;
    Vec() {}
    Vec(const double _x, const double _y) : x(_x), y(_y) {}
    Vec(const Vec &p, const Vec &q) : x(q.x - p.x), y(q.y - p.y) {}
    void rd() {
        x = static_cast<int>(io);
        y = static_cast<int>(io);
    }
    double norm() {
        return x * x + y * y;
    }
    Vec operator * (const double a) {
        return Vec(a * x, a * y);
    }
    Vec operator / (const double a) {
        return Vec(x / a, y / a);
    }
    Vec operator + (const Vec &a) {
        return Vec(a.x + x, a.y + y);
    }
} a, b, c, d;
double dist(const Vec &p, const Vec &q) {
    return sqrt(Vec(p, q).norm());
}
int v0, v1, v2;
double l1, l2;
double calc2(const double d1, const double d2) {
    return dist(dcmp(l1) == 0 ? a : (a + (Vec(a, b) * d1) / l1), dcmp(l2) == 0 ? d : (d + (Vec(d, c) * d2) / l2)) / v0 + d1 / v1 + d2 / v2;
}
double calc1(const double d1) {
    static double l, r, rx, x, t;
    l = 0;
    r = l2;
    while (r - l > eps) {
        t = (r - l) / 3;
        x = l + t;
        rx = r - t;
        if (calc2(d1, x) < calc2(d1, rx))
            r = rx;
        else
            l = x;
    }
    return calc2(d1, (l + r) / 2);
}
int main() {
    static double l, r, rx, x, t;
    a.rd();
    b.rd();
    c.rd();
    d.rd();
    v1 = io;
    v2 = io;
    v0 = io;
    r = l1 = dist(a, b);
    l2 = dist(c, d);
    l = 0;
    while (r - l > eps) {
        t = (r - l) / 3;
        x = l + t;
        rx = r - t;
        if (calc1(x) < calc1(rx))
            r = rx;
        else
            l = x;
    }
    printf("%.2f\n", calc1((l + r) / 2));

    return 0;
}
