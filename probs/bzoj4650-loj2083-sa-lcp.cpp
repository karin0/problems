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

typedef long long ll;
const int N = 30005;
int lg[N];
struct SA {
    int rk[N], sa[N], ht[N], st[20][N];
    void build(char *s, int n, int m = 128) {
        static int fir[N], sec[N], tmp[N], cnt[N], i, j, k, l;
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
        --n;

        for (k = 0, i = 0; i < n; ++i) {
            if (k)
                --k;
            for (j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
            st[0][rk[i]] = k;
        }

        for (j = 1; (1 << j) <= n; ++j)
            for (i = 2; i + (1 << j) - 1 <= n; ++i)
                st[j][i] = std::min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    int lcp(const int i, const int j) {
        static int l, r, k;
        l = rk[i];
        r = rk[j];
        if (l > r)
            std::swap(l, r);
        ++l;
        k = lg[r - l + 1];
        return std::min(st[k][l], st[k][r - (1 << k) + 1]);
    }
} sa, rsa;
char s[N], rs[N];
int n, f[N << 1], g[N << 1];
inline int lcp(const int i, const int j) {
    return sa.lcp(i, j);
}
inline int lcs(const int i, const int j) {
    return rsa.lcp(n - i - 1, n - j - 1);
}
int main() {
    static int ks, i, j, l, x, y, on = 1, t;
    static ll ans;
    ks = io;
    if (!ks)
        return 0;
    for (; ; --ks) {
        io.gs(s);
        for (i = 0; rs[i] = s[i]; ++i);
        n = i;
        std::reverse(rs, rs + n);
        sa.build(s, n);
        rsa.build(rs, n);
        if (n > on) {
            rep (i, on + 1, n)
                lg[i] = lg[i >> 1] + 1;
            on = n;
        }
        t = n >> 1;
        for (l = 1; l <= t; ++l) {
            for (i = 0, j = l; j < n; i += l, j += l) if (s[i] == s[j]) {
                x = std::max(j - lcs(i, j), i);
                y = std::min(i + lcp(i, j), j);
                if (y - x > 0) {
                    ++f[x + l];
                    --f[y + l];
                    ++g[x - l + 1];
                    --g[y - l + 1];
                }
            }
        }
        re (i, 1, n) {
            f[i] += f[i - 1];
            g[i] += g[i - 1];
        }
        re (i, 1, n - 1)
            ans += (ll)f[i] * g[i + 1];
        io.print(ans);
        if (ks == 1)
            break;
        ans = 0;
        std::fill(f, f + n + n + 1, 0);
        std::fill(g, g + n + n + 1, 0);
    }
    io.flush();
    return 0;
}

