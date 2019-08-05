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

const int N = 100003;
char s[N << 1]; // ***
int n, r[N << 1];
void manacher() { // require that s[] is processed
    static int i, rt, pos;
    for (i = rt = pos = 0; i < n; ++i) {
        int &ri = r[i];
        for (ri = rt > i ? std::min(r[2 * pos - i], rt - i) : 1; s[i + ri] == s[i - ri]; ++r[i]);
        if (i + ri > rt)
            rt = i + ri, pos = i;
    }
    /* re (i, 0, n)
        printf("%d: %c, %d\n", i, s[i], r[i]); */
}
inline void upd(int &x, const int v) {
    x = std::max(x, v);
}

int main() {
    static int i, ml[N << 1], mr[N << 1], d, ans;
    static char os[N], *p, *q = s;
    io.gs(os);
    *q++ = '#';
    for (p = os; *p; ++p) {
        *q++ = *p;
        *q++ = '#';
    }
    n = q - s;
    manacher();
    re (i, 0, n) {
        d = r[i] - 1;
        if (i - d >= 0)
            upd(mr[i - d], d);
        if (i + d < n)
            upd(ml[i + d], d);
    }
    for (i = 2; i < n; i += 2)
        upd(mr[i], mr[i - 2] - 2);
    for (i = n - 3; i >= 0; i -= 2)
        upd(ml[i], ml[i + 2] - 2);
    for (i = 0; i < n; i += 2)
        upd(ans, ml[i] + mr[i]);
    io.print(ans);

    io.flush(); // ***
    return 0;
}
