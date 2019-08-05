#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
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
typedef long long ll;
const int pri[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127}, pc = 31;
struct Item {
    ll v;
    int mfi, f1c, f2c;
    bool operator < (const Item &rhs) const {
        return v < rhs.v;
    }
};
std::priority_queue<Item> pq;
int main() {
    static ll n, a, b;
    static int k, i, t, p;
    static Item x;
    n = io;
    k = io;
    rep (i, 1, pc) {
        p = pri[i];
        b = n / p;
        // for (a = 1, t = -1; a * p <= n; a *= p, ++t); // ** it's wrong desu
        for (a = 1, t = -1; a <= b; a *= p, ++t);
        pq.push((Item){a, i, t, 0});
    }
    while (--k) {
        x = pq.top();
        pq.pop();
        if (x.mfi)
            pq.push((Item){x.v / pri[x.mfi] * pri[x.mfi - 1], x.mfi - 1, 1, x.f1c - 1});
        if (x.f2c)
            pq.push((Item){x.v / pri[x.mfi + 1] * pri[x.mfi], x.mfi, x.f1c + 1, x.f2c - 1});
    }
    io.print(pq.top().v);
    io.pc('\n');
    io.flush(); // ***
    return 0;
}
