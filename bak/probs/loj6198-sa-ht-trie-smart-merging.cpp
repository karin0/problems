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

const int N = 100003, W = 17;
namespace sa {
    int rk[N], sa[N], ht[N];
    void calc_sa(char *s, int n, int m = 128) {
        static int fir[N], sec[N], tmp[N], cnt[N], i, l;
        static bool uni;
        s[n] = 0;
        ++n;
        std::fill(cnt, cnt + m, 0);
        re (i, 0, n)
            ++cnt[s[i]];
        re (i, 1, m)
            cnt[i] += cnt[i - 1];
        re (i, 0, n)
            rk[i] = cnt[s[i]] - 1;
        for (l = 1; l < n; l <<= 1) {
            re (i, 0, n)
                fir[i] = rk[i], sec[i] = (i + l < n) ? rk[i + l] : 0;
            std::fill(cnt, cnt + n, 0);
            re (i, 0, n)
                ++cnt[sec[i]];
            re (i, 1, n)
                cnt[i] += cnt[i - 1];
            per (i, n - 1, 0)
                tmp[--cnt[sec[i]]] = i;
            std::fill(cnt, cnt + n, 0);
            re (i, 0, n)
                ++cnt[fir[i]];
            re (i, 1, n)
                cnt[i] += cnt[i - 1];
            per (i, n - 1, 0)
                sa[--cnt[fir[tmp[i]]]] = tmp[i];
            uni = true;
            rk[sa[0]] = 0;
            re (i, 1, n) {
                rk[sa[i]] = rk[sa[i - 1]];
                if (fir[sa[i]] == fir[sa[i - 1]] && sec[sa[i]] == sec[sa[i - 1]])
                    uni = false;
                else
                    ++rk[sa[i]];
            }
            if (uni)
                break;
        }
    }
    void calc_ht(char *s, const int n) {
        static int i, j, k;
        for (k = 0, i = 0; i < n - 1; ++i) {
            if (k)
                --k;
            for (j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
            ht[rk[i]] = k;
        }
    }
    inline void init(char *s, const int n) {
        calc_sa(s, n);
        calc_ht(s, n);
    }
}
inline bool bit(const int x, const int k) {
    return (x >> k) & 1;
}
struct Trie {
    Trie *ch[2];
    void *operator new (size_t) {
        static Trie pool[N * 20], *curr = pool;
        return curr++;
    }
    /*
    inline void maintain() {
        siz = (ch[0] ? ch[0]->siz : 0) + (ch[1] ? ch[1]->siz : 0) + 1;
    }*/
    void insert(const int x, const int k = W - 1) {
        if (k < 0)
            return;
        int b = bit(x, k);
        if (!ch[b])
            ch[b] = new Trie;
        ch[b]->insert(x, k - 1);
        // maintain();
    }
    int query(const int x) {
        static Trie *o;
        static int k, b, res;
        o = this;
        res = 0;
        for (k = W - 1; k >= 0; --k) {
            b = bit(x, k);
            if (o->ch[b ^ 1])
                o = o->ch[b ^ 1], res = (res << 1) | 1;
            else
                o = o->ch[b], res <<= 1;
        }
        return res;
    }
} *trie[N];
Trie *merge(Trie *u, Trie *v) {
    if (!u)
        return v;
    if (!v)
        return u;
    /*
    if (u->siz < v->siz)
        std::swap(u, v);*/
    u->ch[0] = merge(u->ch[0], v->ch[0]);
    u->ch[1] = merge(u->ch[1], v->ch[1]);
    // u->maintain();
    return u;
}
namespace uf {
    int fa[N];
    void init(const int n) {
        static int i;
        rep (i, 0, n)
            fa[i] = i;
    }
    int find(const int x) {
        return fa[x] == x ? x : fa[x] = find(fa[x]);
    }
    inline void link(const int x, const int y) { // x <- y
        fa[y] = x;
    }
}
int n, w[N], suf[N], ht[N], lb[N], rb[N], ww[N];
char s[N];
inline bool cmp(const int i, const int j) {
    return ht[i] > ht[j];
}
int merge(int u, int v) {
    static int res, i;
    if (u == v)
        return -n;
    if (rb[u] - lb[u] < rb[v] - lb[v]) // u <- v
        std::swap(u, v);
    res = 0;
    rep (i, lb[v], rb[v])
        res = std::max(res, trie[u]->query(ww[i]));
    // rep (i, lb[v], rb[v])
    //    trie[u]->insert(w[sa::sa[i]]);
    trie[u] = merge(trie[u], trie[v]);
    lb[u] = std::min(lb[u], lb[v]);
    rb[u] = std::max(rb[u], rb[v]);
    uf::link(u, v);
    return res;
}
int main() {
    static int i, ans;
    n = io;
    io.gs(s);
    sa::init(s, n);
    uf::init(n);
    re (i, 0, n)
        w[i] = io;
    re (i, 1, n) {
        lb[i] = rb[i] = i;
        ht[i] = sa::ht[i + 1];
        suf[i] = i;
        trie[i] = new Trie;
        trie[i]->insert(ww[i] = w[sa::sa[i]]);
    }
    std::sort(suf + 1, suf + n, cmp);
    re (i, 1, n)
        ans = std::max(ans, ht[suf[i]] + merge(uf::find(suf[i]), uf::find(suf[i] + 1))); // printf("suf[%d] = %d, ht[suf[%d]] = %d\n", i,suf[i],i,ht[suf[i]]);
    io.print(ans);
    io.flush(); // ***
    return 0;
}
