#include <cstdio>
#include <cstring>
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
const int N = 100005;
namespace sa {
    int rk[N], sa[N], ht[N];
    void calc_sa(char *s, int n, int m = 128) {
        static int fir[N], sec[N], tmp[N], cnt[N], i, l;
        static bool uni;
        ++n;
        s[n - 1] = 0;
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
        for (k = 0, i = 0; i < n; ++i) {
            if (k)
                --k;
            for (j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
            ht[rk[i]] = k;
        }
    }
}
char s[N];
int n;
int main() {
    static int i;
    io.gs(s);
    n = strlen(s);
    sa::calc_sa(s, n);
    sa::calc_ht(s, n);
    for (i = 1; i <= n; ++i)
        io.print(sa::sa[i] + 1, false), io.pc(i == n ? '\n' : ' ');
    for (i = 2; i <= n; ++i)
        io.print(sa::ht[i], false), io.pc(i == n ? '\n' : ' ');
    
    // for (i = 0; i <= n; ++i)
    //    printf("str[%d] = %c, sa[%d] = %d, rk[%d] = %d, ht[%d] = %d\n", i, s[i], i, sa::sa[i], i, sa::rk[i], i, sa::ht[i]); 
   
    io.flush();
    return 0;
}

