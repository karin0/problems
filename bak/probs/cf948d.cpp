#include <new>
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

const int N = 300003, W = 29;
inline bool bit(const int x, const int k) {
    return (x >> k) & 1;
}
struct Trie *curr;
struct Trie {
    Trie *ch[2], *fa;
    int cnt;
    Trie(Trie *_f = NULL) : fa(_f), cnt(0) {}

    void insert(const int x, const int k = W) {
        ++cnt;
        if (k < 0)
            return;
        int v = bit(x, k);
        if (!ch[v])
            ch[v] = new (curr++) Trie(this);
        ch[v]->insert(x, k - 1);
    }
    /*
    bool find(const int x, const int k = W) {
        printf("finding %d, %d ..\n", x, k);
        if (k < 0)
            return this != nil;
        return this != nil && ch[bit(x, k)]->find(x, k - 1);
    }*/
} pool[N * W], *root;
inline void init() {
    curr = pool;
    root = new (curr++) Trie;
}
int i;
int query(const int x) {
    static Trie *p, *q;
    static int res, k;
    static bool v;
    p = root;
    for (res = 0, k = W; k >= 0; --k) {
        v = bit(x, k);
        if (p->ch[v] && p->ch[v]->cnt > 0)
            p = p->ch[v], res = res << 1; // printf("Og %d\n", v);
        else
            p = p->ch[!v], res = (res << 1) | 1 ;// printf("Go %d\n", !v);
    }
    /*
    q = NULL;
    while (p->fa && !(p->ch[0] && p->ch[1]))
        q = p, p = p->fa;
    p->ch[p->ch[1] == q] = NULL;
    */
    while (p)
        --p->cnt, p = p->fa;
    return res;
}

int main() {
    static int n, a[N];
    init();
    n = io;
    rep (i, 1, n)
        a[i] = io;
    rep (i, 1, n)
        root->insert(io);
    rep (i, 1, n) {
        io.print(query(a[i]));
        io.pc(i == n ? '\n' : ' ');
    }
    io.flush();
    return 0;
}