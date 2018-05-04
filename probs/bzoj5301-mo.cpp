#include <cstdio>
#include <cctype>
#include <cmath>
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

typedef long long ll;
const int N = 100005, R = 1 << 17;
int n, k, a[N], bel[N], s;
struct Query {
    int l, r;
    ll *ans;
    inline bool operator < (const Query &rhs) const {
        return bel[l] < bel[rhs.l] || (bel[l] == bel[rhs.l] && r < rhs.r);
    }
} qwq[N];
int l, r, cnt[R];
ll res;
int main() {
    static int m, i, t;
    static ll ans[N];
    n = (int)io + 1;
    m = io;
    k = io;
    s = sqrt((double)n * n / m);
    re (i, 1, n) {
        a[i] = a[i - 1] ^ (int)io;
        bel[i] = bel[i - 1];
        if (++t >= s)
            ++bel[i], t = 0;
    }
    re (i, 0, m) {
        Query &q = qwq[i];
        q.l = (int)io - 1;
        q.r = io;
        q.ans = &ans[i];
    }
    std::sort(qwq, qwq + m);
    cnt[0] = 1;
    re (i, 0, m) {
        const Query &q = qwq[i];
        while (l < q.l)
            --cnt[a[l]], res -= cnt[k ^ a[l++]];
        while (q.r < r)
            --cnt[a[r]], res -= cnt[k ^ a[r--]];
        while (q.l < l)
           res += cnt[k ^ a[--l]], ++cnt[a[l]]; 
        while (r < q.r)
           res += cnt[k ^ a[++r]], ++cnt[a[r]]; 
        *q.ans = res;
    }
    re (i, 0, m)
        io.print(ans[i]);

    io.flush();
    return 0;
}
