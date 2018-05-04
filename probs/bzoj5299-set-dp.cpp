#include <cstdio>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <bitset>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#define VAL(x) fprintf(stderr, #x " = %d\n", x)
#define LOG(...) fprintf(stderr, __VA_ARGS__)

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

const int N = 21, S = (1 << 20) + 3, mo = 100000007;
int n, f[S][N], obs[N][N];
struct Pt {
    int x, y;
} qaq[N];
inline bool ss(const int a, const int b) {
    return (a >= 0 && b >= 0) || (a <= 0 && b <= 0); // *****
}
inline bool in(const Pt &p, const Pt &a, const Pt &b) {
    return (a.x - p.x) * (b.y - p.y) == (a.y - p.y) * (b.x - p.x) && ss(a.x - p.x, p.x - b.x) && ss(a.y - p.y, p.y - b.y);
}
inline bool bit(const int x, const int k) {
    return (x >> k) & 1;
}
inline void add(int &x, const int v) {
    x += v;
    if (x >= mo)
        x -= mo;
}
int main() {
    static int i, j, k, uni, ans, tmp, siz;
    n = io;
    uni = 1 << n;
    re (i, 0, n) {
        qaq[i].x = io;
        qaq[i].y = io;
    }
    re (i, 0, n) re (j, 0, i) {
        re (k, 0, n) if (i != k && j != k && in(qaq[k], qaq[i], qaq[j]))
            obs[i][j] |= 1 << k;
        //printf("obs %d %d = ", i, j);
        //std::cout << std::bitset<16>(obs[i][j]) << std::endl;
        obs[j][i] = obs[i][j];
    }
    re (i, 0, n)
        f[1 << i][i] = 1;
    re (i, 1, uni)
        re (j, 0, n) if (bit(i, j))
            re (k, 0, n) if (!bit(i, k) && (obs[j][k] | i) == i)
                add(f[i | (1 << k)][k], f[i][j]);
    re (i, 15, uni) {
        tmp = siz = 0;
        re (j, 0, n) if (bit(i, j))
            add(tmp, f[i][j]), ++siz;
        if (siz >= 4)
            add(ans, tmp);
    }
    io.print(ans);

    io.flush();
    return 0;
}
