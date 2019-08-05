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

const int N = 502;
int n, m;
char a[N][N];
int main() {
    static int i, j, nx, ny;
    static bool failed;
    n = io;
    m = io;
    rep (i, 1, n) {
        io.gs(a[i] + 1);
    }
    rep (i, 1, n) rep (j, 1, m) if (a[i][j] == 'S') {
        nx = i - 1;
        ny = j;
        if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
            char &x = a[nx][ny];
            if (x == 'W') {
                failed = true;
                goto end;
            }
            if (x == '.')
                x = 'D';
        }
        nx = i + 1;
        ny = j;
        if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
            char &x = a[nx][ny];
            if (x == 'W') {
                failed = true;
                goto end;
            }
            if (x == '.')
                x = 'D';
        }
        nx = i;
        ny = j - 1;
        if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
            char &x = a[nx][ny];
            if (x == 'W') {
                failed = true;
                goto end;
            }
            if (x == '.')
                x = 'D';
        }
        nx = i;
        ny = j + 1;
        if (1 <= nx && nx <= n && 1 <= ny && ny <= m) {
            char &x = a[nx][ny];
            if (x == 'W') {
                failed = true;
                goto end;
            }
            if (x == '.')
                x = 'D';
        }
    }
end:;
    if (failed)
        io.puts("No\n");
    else {
        io.puts("Yes\n");
        rep (i, 1, n)
            io.puts(a[i] + 1), io.pc('\n');
    }
    io.flush(); // ***
    return 0;
}
