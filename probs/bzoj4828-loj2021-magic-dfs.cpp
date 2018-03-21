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

const int N = 102, M = 22, S = 2e7, pri[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 91, 97, 101, 103};
inline void upd(int &x, const int v) {
    x = std::max(x, v);
}
int na, mxc, rcnt, fs[S], ts[S];
void dfs(const int i, long long f) {
    int p = pri[i];
    if (p > na)
        return;
    fs[rcnt++] = f;
    for (; f <= mxc; f *= p)
        dfs(i + 1, f);
}
int get_t(const int x) {
    static int ret, i, cnt, t, j;
    ret = x + 1;
    for (i = std::min(na, x - 1); i > 0; --i) {
        if (x % i)
            continue;
        cnt = i + 1; 
        t = x;
        for (j = i; j > 1 && t > 1; --j) for (; t % j == 0; t /= j, ++cnt);
        if (t == 1)
            ret = std::min(ret, cnt);
        else
            return ret;
    }
    return ret;
}
int main() {
    static int n, m, mc, i, j, k, a[N], w[N], cs[M], c, x, dp[N][N], nw, ok, mv;
    n = io, m = io, mc = io;
    rep (i, 1, n)
        a[i] = io;
    rep (i, 1, n)
        w[i] = io;
    rep (i, 1, m)
        cs[i] = io, upd(mxc, cs[i]);
    rep (i, 1, n) rep (j, a[i], mc)
        dp[i][j] = -2;
    dp[1][mc] = 0;
    rep (i, 1, n) rep (j, a[i], mc) {
        x = dp[i][j];
        if (x < 0)
            continue;
        nw = std::min(j - a[i] + w[i], mc);
        if (nw >= 0)
            upd(dp[i + 1][nw], x);
        nw = j - a[i];
        if (nw >= 0)
            upd(dp[i + 1][nw], x + 1);
    }
    na = 0;
    rep (i, 2, n + 1)
        rep (j, 0, mc)
            upd(na, dp[i][j]);
    na = 100, mxc = 1e8;
    dfs(0, 1);
    fs[++rcnt] = 0;
    printf("%d\n", rcnt);
    std::sort(fs, fs + rcnt);
    rcnt = std::unique(fs, fs + rcnt) - fs;
    ts[0] = 0;
    re (i, 1, rcnt)
        ts[i] = fs[i] - get_t(fs[i]); //  printf("%d %d: f = %d, t = %d\n", na, i, fs[i], fs[i] - ts[i]);
    rep (k, 1, m) {
        c = cs[k];
        x = c - na;
        ok = 0;
        j = 0;
        mv = -0x7f7f7f7f;
        for (i = rcnt - 1; i >= 0; --i) {
            while (j < rcnt && fs[i] + fs[j] <= c)
                upd(mv, ts[j]), ++j;
            if (mv + ts[i] >= x) {
                ok = 1;
                break;
            }
        }
        io.print(ok);
    }

    io.flush(); // ***
    return 0;
}
