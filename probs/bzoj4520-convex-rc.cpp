#include <cstdio>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <queue>
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

typedef long long ll;
const int N = 100003;

struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator < (const Point &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
    Point operator - (const Point &rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }
    ll norm() const {
        return (ll)x * x + (ll)y * y;
    }
} po[N], co[N];
inline Point vec(const Point &a, const Point &b) {
    return b - a;
}
inline ll cross(const Point &a, const Point &b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
}
struct Rec {
    ll dis;
    int a, b;
    bool operator < (const Rec &rhs) const {
        return dis < rhs.dis;
    }
};
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
int a_ret, b_ret;
int rc(int n) {
    static int k, i, ta, tb;
    static Point s;
    static ll ans, ca, cb;
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
        ca = vec(co[i], co[k]).norm();
        cb = vec(co[i + 1], co[k + 1]).norm();
        if (ca < cb)
            ca = cb, ta = i + 1, tb = k + 1;
        else
            ta = i, tb = k;
        if (ans < ca)
            ans = ca, a_ret = ta, b_ret = tb;
    }
    return ans;
}
std::priority_queue<Rec> pq;
int main() {
    static int i, n, k;
    n = io;
    k = io;
    re (i, 0, n)
        po[i].x = io, po[i].y = io;
    while (k--) {
        rc(build_convex(n));

    }

    io.flush();
    return 0;
}
