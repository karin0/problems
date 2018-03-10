#include <cstdio>
#include <cctype>
#include <cstring>
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

const int N = 100005;
char str[N];
int n, rk[N], sa[N], ht[N];
void build(int m) {
    static int fir[N], sec[N], tmp[N], cnt[N], i, l;
    static bool uni;
    n = strlen(str) + 1;
    str[n - 1] = 0;
    std::fill(cnt, cnt + m, 0);
    for (i = 0; i < n; ++i)
        ++cnt[str[i]];
    for (i = 1; i < m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = 0; i < n; ++i)
        rk[i] = cnt[str[i]] - 1;
    for (l = 1; l < n; l <<= 1) {
        for (i = 0; i < n; ++i)
            fir[i] = rk[i], sec[i] = (i + l < n) ? rk[i + l] : 0;
        std::fill(cnt, cnt + n, 0);
        for (i = 0; i < n; ++i)
            ++cnt[sec[i]];
        for (i = 1; i < n; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; --i)
            tmp[--cnt[sec[i]]] = i;
        std::fill(cnt, cnt + n, 0);
        for (i = 0; i < n; ++i)
            ++cnt[fir[i]];
        for (i = 1; i < n; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; --i)
            sa[--cnt[fir[tmp[i]]]] = tmp[i];
        uni = true;
        rk[sa[0]] = 0;
        for (i = 1; i < n; ++i) {
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
void init_ht() {
    static int i, j, k;
    for (k = 0, i = 0; i < n - 1; ++i) {
        printf("HT i = %d\n", i);
        if (k)
            --k;
        for (j = sa[rk[i] - 1]; str[i + k] == str[j + k]; ++k);
        ht[rk[i]] = k;
    }
}
int main() {
    static int i;
    scanf("%s", str);
    build(128);
    init_ht();
    --n;
    for (i = 1; i <= n; ++i)
        printf("%d%c", sa[i] + 1, i == n ? '\n' : ' ');
    for (i = 2; i <= n; ++i)
        printf("%d%c", ht[i], i == n ? '\n' : ' ');
    for (i = 0; i <= n; ++i)
        printf("str[%d] = %c, sa[%d] = %d, rk[%d] = %d, ht[%d] = %d\n", i, str[i], i, sa[i], i, rk[i], i, ht[i]);
    for (i = 0; i <= n; ++i) {
        printf("rk %d: %s\n", i, str + sa[i]);
    }

    return 0;
}


