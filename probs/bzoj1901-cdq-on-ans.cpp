#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define cccc(x) std::cerr << #x " = " << x << std::endl
    #define ccccc(x) std::cerr << x << std::endl
#else
    #define ccc(x) 0
    #define cccc(x) 0
    #define ccccc(x) 0
#endif

struct IO {
    static const int L = 1000000;
    char a[L], b[L], *s, *t, *p;
    IO() : p(b) {}
    ~IO() {
        flush();
    }
    char gc() {
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
    void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 10002, M = 10002;
struct Oper {
    int l, r, x, *ans;
} q;
int n, td[2][M * 3], cd[2];
namespace bit {
    int c[N];
    void add(int i, int x) {
        for (; i <= n; i += i & -i)
            c[i] += x;
    }
    int query(int i) {
        static int res;
        for (res = 0; i; i -= i & -i)
            res += c[i];
        return res;
    }
}
void cdq(std::queue<Oper> &a, int l, int r) {
    if (a.empty() || l >= r)
        return;
    if (l + 1 == r) {
        while (!a.empty()) {
            q = a.front();
            a.pop();
            if (q.ans)
                *q.ans = l;
        }
        return;
    }
    int mid = l + ((r - l) >> 1), t, rt;
    std::queue<Oper> a1, a2;
    while (!a.empty()) {
        q = a.front();
        a.pop();
        if (q.ans) {
            t = bit::query(q.r) - bit::query(q.l - 1);
            if (t + 1 <= q.x)  // ***
                q.x -= t, a2.push(q);
            else
                a1.push(q); 
        } else {
            t = (rt = q.r) ? -1 : 1;
            if (q.x < mid) {
                bit::add(q.l, t);
                td[rt][++cd[rt]] = q.l;
                a1.push(q);
            } else
                a2.push(q);
        }
    }
    rep (t, 1, cd[0])
        bit::add(td[0][t], -1);
    rep (t, 1, cd[1])
        bit::add(td[1][t], 1);
    cd[0] = cd[1] = 0;
    cdq(a1, l, mid);
    cdq(a2, mid, r);
}
int main() {
    static int m, mx, i, seq[N], ans[M], qc;
    std::queue<Oper> a;
    n = io;
    m = io;
    rep (i, 1, n) {
        q.l = i;
        q.r = 0;
        q.x = seq[i] = io;
        mx = std::max(mx, q.x);
        a.push(q);
    }
    rep (i, 1, m) {
        static char opt[5];
        io.gs(opt);
        if (opt[0] == 'C') {
            q.l = io;
            q.r = 1;
            q.x = seq[q.l];
            a.push(q);
            q.r = 0;
            q.x = seq[q.l] = io;
            mx = std::max(mx, q.x);
            a.push(q);
        } else {
            q.l = io;
            q.r = io;
            q.x = io;
            q.ans = &ans[++qc];
            a.push(q);
        }
    }
    cdq(a, 0, mx + 3);
    rep (i, 1, qc)
        io.print(ans[i]);

    return 0;
}
