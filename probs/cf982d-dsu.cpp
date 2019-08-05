#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define SAY(x) std::cerr << #x " = " << x << std::endl
#else
    #define SAY(x) 0
#endif

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
    inline void flush() const {
        fwrite(b, 1, p - b, stdout); // p = b;
    }
} io;

const int N = 100003;
int n, a[N], b[N], ans[N];
namespace dsu {
    int fa[N], sz[N];
    void init() {
        static int i;
        rep (i, 1, n)
            fa[i] = i, sz[i] = 1;
    }
    int find(const int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        fa[x] = y;
        sz[y] += sz[x];
    }
    int siz(const int x) {
        return sz[find(x)];
    }
}
bool vis[N];
int s[N], ss, sum;
void dec1(const int x) {
    --sum;
    if (s[x] == 1)
        s[x] = 0, --ss;
    else
        --s[x];
}
void inc1(const int x) {
    ++sum;
    if (s[x])
        ++s[x];
    else
        s[x] = 1, ++ss;
}
bool cmp(const int i, const int j) {
    return a[i] < a[j];
}
int main() {
    static int i, p;
    n = io;
    dsu::init();
    rep (i, 1, n) {
        a[i] = io;
        b[i] = i;
    }
    std::sort(b + 1, b + n + 1, cmp);
    rep (i, 1, n) {
        static bool fl, fr;
        static int sl, sr;
        p = b[i];
        vis[p] = true;
        fl = p > 1 && vis[p - 1];
        fr = p < n && vis[p + 1];
        if (fl && fr) {
            dec1(sl = dsu::siz(p - 1));
            dec1(sr = dsu::siz(p + 1));
            inc1(sl + sr + 1);
            dsu::unite(p, p - 1);
            dsu::unite(p, p + 1);
        } else if (fl) {
            dec1(sl = dsu::siz(p - 1));
            inc1(sl + 1);
            dsu::unite(p, p - 1);
        } else if (fr) {
            dec1(sr = dsu::siz(p + 1));
            inc1(sr + 1);
            dsu::unite(p, p + 1);
        } else {
            inc1(1);
        }/*
        SAY(i);
        SAY(p);
        SAY(a[p]);
        SAY(sl);
        SAY(sr);
        puts("");*/
        if (ss == 1 && !ans[sum]) {
            ans[sum] = i;
            //printf("!!!!!!! ans[%d ]=%d\n",x,i);
        }
    }
    per (i, n, 1)
        if (ans[i]) {
            io.print(a[b[ans[i]]] + 1);
            //printf("find x = %d, i = %d, ans = %d\n", x, i, ans[i]);
            break;
        }

    io.flush();
    return 0;
}
