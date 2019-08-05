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

int n, m, a[103][103], c[103][103];
int main() {
    static int i, j, di, dj, ni, nj;
    static char s[103];
    n = io;
    m = io;
    rep (i, 1, n) {
        io.gs(s + 1);
        rep (j, 1, m) {
            char x = s[j];
            if (x == '.')
                a[i][j] = 0;
            else if (x == '*') {
                a[i][j] = -1;// printf("%d %d is *\n",i,j);
                /*
                c[i][j] = -1;
                rep (di, -1, 1)
                    rep (dj, -1, 1) {
                        if (di == 0 && dj == 0)
                            continue;
                        ni = i + di;
                        nj = j + dj;
                        if (1 <= ni && ni <= n && 1 <= nj && nj <= m)
                            ++c[ni][nj];
                    }*/
            } else
                a[i][j] = x - '0';
        }
    }
    rep (i, 1, n) {
        rep (j, 1, m) {
            int x = a[i][j], cnt = 0;
            if (x < 0)
                continue;
            rep (di, -1, 1)
                rep (dj, -1, 1) {
                    if (di == 0 && dj == 0)
                        continue;
                    ni = i + di;
                    nj = j + dj;
                    if (1 <= ni && ni <= n && 1 <= nj && nj <= m && a[ni][nj] == -1)
                        ++cnt;// printf("found %d %d\n",ni,nj);
                }
            if (cnt != x) {
                //printf("Bad at %d, %d, cnt = %d, x = %d\n",i,j,cnt,x);
                io.ps("NO");
                io.flush();
                return 0;
            }
        }
    }
    io.ps("YES");

    io.flush();
    return 0;
}
