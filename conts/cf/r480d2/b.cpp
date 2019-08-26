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

int main() {
    static int n, k, i, j;
    static bool mat[6][105];
    n = io;
    k = io;
    if ((k & 1) == 0) {
        k >>= 1;
        rep (i, 2, 2 + k - 1)
            mat[2][i] = mat[3][i] = 1;
    } else {
        if (k >= n - 2) {
            rep (i, 2, n - 1)
                mat[2][i] = 1;
            k -= n - 2;
            k >>= 1;
            rep (i, 1, k)
                mat[3][1 + i] = mat[3][n - i] = 1;
        } else {
            mat[2][(n + 1) >> 1] = 1;
            k -= 1;
            k >>= 1;
            rep (i, 1, k)
                mat[3][1 + i] = mat[3][n - i] = 1;
        }
    }
    io.ps("YES");
    rep (i, 1, 4) {
        rep (j, 1, n) {
            io.pc(mat[i][j] ? '#' : '.');
        }
        io.pc('\n');
    }

    io.flush();
    return 0;
}
