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

const int N = 100005;
inline void chmin(int &x, const int v) {
    x = std::min(x, v);
}
inline void chmax(int &x, const int v) {
    x = std::max(x, v);
}
namespace bit {
    int n, c[N];
    inline int lowbit(const int x) {
        return x & -x;
    }
    int query(int i) {
        static int res;
        for (res = 0; i > 0; i -= lowbit(i))
            chmax(res, c[i]);
        return res;
    }
    void update(int i, const int x) {
        for (; i <= n; i += lowbit(i))
            chmax(c[i], x);
    }
    void clear(int i) {
        for (; i <= n && c[i]; i += lowbit(i)) // ?
            c[i] = 0;
    }
}
int n, a[N], mn[N], mx[N], ans[N];
struct Query {
    int x, y, z;
    inline bool operator < (const Query &rhs) const {
        return (y < rhs.y) || (y == rhs.y && x < rhs.x);  // *****
    }
} tmp[N];
void cdq(const int l, const int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1, i, cnt = 0;
    cdq(l, mid);
    for (i = l; i <= mid; ++i)
        tmp[++cnt] = (Query){i, mx[i], a[i]};
    for (; i <= r; ++i)
        tmp[++cnt] = (Query){i, a[i], mn[i]};
    std::sort(tmp + 1, tmp + cnt + 1);
    for (i = 1; i <= cnt; ++i) {
        const Query &q = tmp[i];
        if (q.x <= mid)
            bit::update(q.z, ans[q.x]);
        else
            chmax(ans[q.x], bit::query(q.z) + 1);   // ******** !
    }
    for (i = l; i <= mid; ++i)
        bit::clear(a[i]);
    cdq(mid + 1, r);
}
int main() {
    static int i, m, x, y;
    n = io;
    m = io;
    rep (i, 1, n) {
        chmax(bit::n, mn[i] = mx[i] = a[i] = io);
        ans[i] = 1;
    }
    rep (i, 1, m) {
        x = io;
        y = io;
        chmin(mn[x], y);
        chmax(mx[x], y);
    }
    // f[i] = max{ f[j] + 1 | j < i, mx[j] <= a[i], a[j] <= mn[i] }
    cdq(1, n);
    io.print(*std::max_element(ans + 1, ans + n + 1));

    io.flush();
    return 0;
}
