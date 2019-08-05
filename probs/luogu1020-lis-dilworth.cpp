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
    bool eoff;
    IO() : p(b) {}
    inline char gc() {
        if (s == t)
            t = (s = a) + fread(a, 1, L, stdin);
        return s == t ? 0 : *s++;
    }
    template <class T>
    bool read(T &x) {
        static char c;
        if (eoff)
            return false;
        for (c = gc(); !isdigit(c); c = gc())
            if (c == 0)
                return false;
        x = c - '0';
        for (c = gc(); isdigit(c); c = gc())
            x = x * 10 + (c - '0');
        eoff = c == 0;
        return true;
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
            for (q = c; x; x = y)
                y = x / 10, *q++ = x - y * 10 + '0';
            while (q != c)
                pc(*--q);
        }
        if (nl)
            pc('\n');
    }
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;
const int N = 100005;
struct LIS {
    int f[N], *p, ans, i;
    int lis(const int a[], const int n) {
        // if (n <= 0)
        //     return 0;
        f[ans = 1] = a[1];
        for (i = 2; i <= n; ++i) {
            *(p = std::lower_bound(f + 1, f + ans + 1, a[i])) = a[i];
            ans = std::max(ans, (int)(p - f));
        }
        return ans;
    }
    int lnds(const int a[], const int n) {
        // if (n <= 0)
        //     return 0;
        f[ans = 1] = a[1];
        for (i = 2; i <= n; ++i) {
            *(p = std::upper_bound(f + 1, f + ans + 1, a[i])) = a[i];
            ans = std::max(ans, (int)(p - f));
        }
        return ans;
    }
} lis;

int a[N], n;
int main() {
    static int i, x;
    while (io.read(a[++n]));
    --n;
    x = lis.lis(a, n);
    for (i = 1; i <= n; ++i)
        a[i] = -a[i];
    io.print(lis.lnds(a, n));
    io.print(x);

    io.flush();
    return 0;
}
