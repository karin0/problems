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

const int N = 201, inf = 0x3f3f3f3f;

int n, d[N][N], f[N][N];
void floyd() {
    static int i, j, k, t, *dk, *di, *fi;
    rep (k, 1, n) {
        dk = d[k];
        rep (i, 1, n) if (i != k) {
            di = d[i];
            fi = f[i];
            rep (j, 1, n) if (i != j && k != j) { 
                t = di[k] + dk[j];
                if (di[j] > t) {
                    di[j] = t;
                    fi[j] = k;
                } else if (di[j] == t)
                    fi[j] = 0;
            }
        }
    }
}
int main() {
    static int m, u, v, i, ans[N], cnt, *du, *fu, *p, *q;
    static bool used[N];
    n = io, m = io;
    rep (u, 1, n) {
        du = d[u];
        rep (v, 1, n)
            du[v] = inf;
        du[u] = 0;
    }
    rep (i, 1, m) {
        u = io, v = io;
        d[u][v] = d[v][u] = io;
    }
    floyd();
    rep (u, 1, n) {
        fu = f[u];
        rep (v, u + 1, n) if (fu[v] && !used[fu[v]])
            ans[cnt++] = fu[v], used[fu[v]] = true;
    }
    if (cnt) {
        std::sort(ans, ans + cnt);
        q = ans + cnt;
        for (p = ans; p != q; ++p)
            io.print(*p), io.pc(' ');
    } else
        io.puts("No important cities.\n");
    io.flush();
    return 0;
}
