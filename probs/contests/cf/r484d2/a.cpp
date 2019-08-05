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

int n, c0, ans;
char s[1005];
int main() {
    static int i;
    n = io;
    io.gs(s + 1);
    c0 = s[1] == '0';
    ans = c0;
    if (n == 1 && c0) {
            io.ps("No");
            io.flush();
            return 0;
    }
    if (n >= 2 && s[1] == '0' && s[2] == '0') {
            io.ps("No");
            io.flush();
            return 0;
    }
    if (n >= 2 && s[n] == '0' && s[n - 1] == '0') {
            io.ps("No");
            io.flush();
            return 0;
    }
    rep (i, 2, n) {
        if (s[i] == '1' && s[i - 1] == '1') {
            io.ps("No");
            io.flush();
            return 0;
        }
        if (s[i] == '0')
            ++c0;
        else
            c0 = 0;
        ans = std::max(ans, c0);
    }
    io.ps(ans <= 2 ? "Yes" : "No");

    io.flush();
    return 0;
}
