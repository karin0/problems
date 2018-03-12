#include <cstdio>
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

const int N = 50007;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator < (const Point &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    int norm() const {
        return x * x + y * y;
    }
} po[N], co[N];
inline Point vec(const Point &a, const Point &b) {
    return b - a;
}
inline int cross(const Point &a, const Point &b) {
    return a.x * b.y - a.y * b.x;
}
int build_convex(int n) {
    static int m, i, k;
    std::sort(po, po + n);
    m = 0;
    re (i, 0, n) {
        while (m > 1 && cross(vec(co[m - 2], co[m - 1]), vec(co[m - 2], po[i])) <= 0)
            --m;
        co[m++] = po[i];
    }
    k = m;
    per (i, n - 1, 0) {
        while (m > k && cross(vec(co[m - 2], co[m - 1]), vec(co[m - 2], po[i])) <= 0)
            --m;
        co[m++] = po[i];
    }
    if (m > 1)
        --m;
    return m;
}
int rc(int n) {
    static int ans, k, i;
    static Point s;
    ans = 0;
    co[n] = co[0];
    k = 1;
    re (i, 0, n) {
        s = vec(co[i + 1], co[i]);
        while (cross(vec(co[i + 1], co[k]), s) < 
               cross(vec(co[i + 1], co[k + 1]), s)) {
            ++k;
            if (k == n)
                k = 0;
        }
        ans = std::max(ans, std::max(vec(co[i], co[k]).norm(), vec(co[i + 1], co[k + 1]).norm()));
    }
    return ans;
}

int main() {
    static int i, n;
    n = io;
    re (i, 0, n)
        po[i].x = io, po[i].y = io;
    printf("%d\n", rc(build_convex(n)));

    io.flush();
    return 0;
}
