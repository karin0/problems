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

const int N = 15 + 7, S2 = (1 << 15) + 7, S3 = 15000000;
int n, m, u, seq[N], psq[N], pos[N], pow3[N], trans[S2][N], dp[S3], to3[S2];
inline bool bit(const int x, const int k) {
    return (x >> k) & 1;
}
int main() {
    static int i, j, s, t, s3, ans;
    n = io;
    m = io;
    re (i, 0, n)
        pos[i] = -1;
    re (i, 0, m) {
        seq[i] = (int)io - 1;
        pos[seq[i]] = i;
    }
    re (i, 0, n) if (pos[i] > 0)
        psq[i] = seq[pos[i] - 1];
    pow3[0] = 1;
    re (i, 1, n)
        pow3[i] = pow3[i - 1] * 3;
    u = (1 << n) - 1;
    rep (s, 0, u) {
        int &x = to3[s];
        re (i, 0, n) if (bit(s, i))
            x += pow3[i];
    }
    rep (s, 0, u) if (__builtin_popcount(s) <= m) {
        static int *ts;
        ts = trans[s];
        re (i, 0, n) if (!bit(s, i)) {
            int &x = ts[i];
            for (j = i + 1; j < n && !bit(s, j); ++j);
            t = s | (1 << i);
            if (j < n)
                t ^= 1 << j;
            if (__builtin_popcount(t) <= m)
                x = t;
        }
    }
    dp[0] = 1;
    rep (s, 0, u) {
        s3 = to3[s];
        for (t = s; ; t = (t - 1) & s) {
            static int x, tr, *tt;
            x = dp[s3 + to3[t]];
            tt = trans[t];
            if (x) {
                re (i, 0, n) {
                    tr = tt[i];
                    if (!bit(s, i) && tr && (pos[i] <= 0 || bit(s, psq[i])))
                        dp[s3 + pow3[i] + to3[tr]] += x;
                }
                if (s == u)
                    ans += x;
            }
            if (!t)
                break;
        }
    }

    io.print(ans);
    io.flush(); // ***
    return 0;
}
