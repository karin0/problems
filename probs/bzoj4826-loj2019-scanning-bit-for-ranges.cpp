#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
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
        return *s++;
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
    inline void flush() {
        fwrite(b, 1, p - b, stdout);
    }
} io;
const int N = 200003;
typedef long long ll;
struct Pair {
    int x, y;
};
struct Query {
    int i;
    ll *ans;
};
int n, m;
struct DS {
    struct BIT {
        ll c[N];
        inline static int lowbit(const int x) {
            return x & -x;
        }
        void add(int i, const ll x) {
            for (; i <= n; i += lowbit(i))
                c[i] += x;
        }
        ll query(int i) const {
            static ll res;
            for (res = 0; i >= 1; i -= lowbit(i))
                res += c[i];
            return res;
        }
    } bit, bit_;
    inline void add(const int l, const int r, const ll x) {
        if (l > r)
            return;
        bit.add(l, x);
        bit_.add(l, x * l);
        if (r < n) {
            bit.add(r + 1, -x);
            bit_.add(r + 1, -x * (r + 1));
        }
    }
    inline ll query_pre(const int i) const {
        return bit.query(i) * (i + 1) - bit_.query(i);
    }
    inline ll query_suf(const int i) const {
        return bit.query(n) * (n + 1) - bit_.query(n) - bit.query(i - 1) * i + bit_.query(i - 1);
    }
} ds, ds1;
int a[N], lb[N], rb[N]; // 前 / 后最近的更大的数的位置
std::vector<int> mod0[N];
std::vector<Pair> mod1[N], mod2[N];
std::vector<Query> qwq1[N], qwq2[N];
ll p1, p2, ans[N];
int main() {
    static int i, l, r, mono[N], top;
    n = io, m = io, p1 = io, p2 = io;
    rep (i, 1, n)
        a[i] = io;

    rep (i, 1, n) {
        while (top > 0 && a[mono[top]] < a[i])
            --top;
        lb[i] = top ? mono[top] : 0;
        mono[++top] = i;
    }
    top = 0;
    per (i, n, 1) {
        while (top > 0 && a[mono[top]] < a[i])
            --top;
        rb[i] = top ? mono[top] : (n + 1);
        mono[++top] = i;
    }
    /* rep (i, 1, n)
        printf("%d : a=%d, lb=%d(%d), rb=%d(%d)\n",i,a[i],lb[i],a[lb[i]],rb[i],a[rb[i]]); */
    rep (i, 1, n) {
        l = lb[i], r = rb[i];
        if (l >= 1) {
            if (r <= n)
                mod0[r].push_back(l), mod1[r].push_back(Pair{l + 1, i - 1});
            mod2[l].push_back(Pair{i + 1, r - 1});
        } else if (r <= n)
            mod1[r].push_back(Pair{l + 1, i - 1});
    }

    rep (i, 1, m) {
        l = io, r = io;
        ans[i] = (r - l) * p1;
        qwq1[r].push_back((Query){l, &ans[i]});
        qwq2[l].push_back((Query){r, &ans[i]});
    }

    rep (i, 1, n) {
        for (std::vector<int>::iterator it = mod0[i].begin(); it != mod0[i].end(); ++it)
            ds.add(*it, *it, p1);
        for (std::vector<Pair>::iterator it = mod1[i].begin(); it != mod1[i].end(); ++it)
            ds.add(it->x, it->y, p2);
        for (std::vector<Query>::iterator it = qwq1[i].begin(); it != qwq1[i].end(); ++it)
            *it->ans += ds.query_suf(it->i);
    }
    per (i, n, 1) {
        for (std::vector<Pair>::iterator it = mod2[i].begin(); it != mod2[i].end(); ++it)
            ds1.add(it->x, it->y, p2);
        for (std::vector<Query>::iterator it = qwq2[i].begin(); it != qwq2[i].end(); ++it)
            *it->ans += ds1.query_pre(it->i);
    }
    rep (i, 1, m)
        io.print(ans[i]);

    io.flush(); // ***
    return 0;
}
