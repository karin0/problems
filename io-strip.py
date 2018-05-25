def strip(s):
    a = [t.strip() for t in s.split('\n')]
    r = ''
    for i in range(len(a) - 1):
        r += a[i]
        if a[i][-1].isalpha() and a[i + 1][0].isalpha():
            r += ' '
    r += a[-1]
    a = [c for c in r]
    for i in range(len(a) - 1):
        if a[i] == ' ' and (not (a[i - 1].isalpha() and a[i + 1].isalpha())):
            a[i] = ''
    return ''.join(a)

s = r'''struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    ~IO() {
        fwrite(b, 1, p - b, stdout); /* p = b; */
    }
    char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return *s++; /* return s == t ? EOF : *s++; */
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
        if ((neg = c == '-'))
            c = gc();
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        return neg ? -x : x;
    }
    void pc(const char c) {
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
} io;'''
# use raw string
print(strip(s))
