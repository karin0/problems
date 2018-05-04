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
int k, a[19], pow3[20], pow5[14], pow7[12];
ll f[19][30][19][13][11][2][2][2];
ll dp(int w, int c2, int c3, int c5, int c7, bool has0, bool pre0, bool lim) {
    if (c2 >= 30 || c3 >= 19 || c5 >= 13 || c7 >= 11)
        return 0;
    ll &ans = f[w][c2][c3][c5][c7][has0][pre0][lim];
    if (ans >= 0)
        return /*
    printf("w = %d, x = %d, c2 = %d, c3 = %d, c5 = %d, c7 = %d, pre0 = %d, lim = %d,   ans = ", w,x,c2,c3,c5,c7,(int)pre0,(int)lim),
            
            printf("%lld (old) \n", ans),*/ ans;
    if (!has0) {
        if ((1ll << c2) > k)
            return ans = 0;
        ll prod = (1ll << c2) * (ll)pow3[c3] * pow5[c5] * pow7[c7];
        if (prod > k || prod == 0)
            return 
        /*printf("w = %d, x = %d, c2 = %d, c3 = %d, c5 = %d, c7 = %d, pre0 = %d, lim = %d,   ans = ", w,x,c2,c3,c5,c7,(int)pre0,(int)lim),
                
                printf("0 !! \n"), */ ans = 0;
    }
    if (w == 0)
        return /*
            
    printf("w = %d, x = %d, c2 = %d, c3 = %d, c5 = %d, c7 = %d, pre0 = %d, lim = %d,   ans = ", w,x,c2,c3,c5,c7,(int)pre0,(int)lim),
            printf("1 !! \n"),*/ ans = (pre0 ? 0 : 1);
    ans = 0;
    int i, nc2, nc3, nc5, nc7, ub;
    if (lim) {
        ub = a[w - 1];
        rep (i, 0, ub) {
            if (has0 || i == 0)
                nc2 = nc3 = nc5 = nc7 = 0;
            else {
                nc2 = c2;
                nc3 = c3;
                nc5 = c5;
                nc7 = c7;
                switch (i) {
                    case 2: nc2 = c2 + 1; break;
                    case 3: nc3 = c3 + 1; break;
                    case 4: nc2 = c2 + 2; break;
                    case 5: nc5 = c5 + 1; break;
                    case 6: nc2 = c2 + 1; nc3 = c3 + 1; break;
                    case 7: nc7 = c7 + 1; break;
                    case 8: nc2 = c2 + 3; break;
                    case 9: nc3 = c3 + 2; break;
                }
            }
            ans += dp(w - 1, nc2, nc3, nc5, nc7, !(pre0 && i == 0) && (has0 || i == 0), pre0 && i == 0, i == ub);
        }
    } else {
        rep (i, 0, 9) {
            if (has0 || i == 0)
                nc2 = nc3 = nc5 = nc7 = 0;
            else {
                nc2 = c2;
                nc3 = c3;
                nc5 = c5;
                nc7 = c7;
                switch (i) {
                    case 2: nc2 = c2 + 1; break;
                    case 3: nc3 = c3 + 1; break;
                    case 4: nc2 = c2 + 2; break;
                    case 5: nc5 = c5 + 1; break;
                    case 6: nc2 = c2 + 1; nc3 = c3 + 1; break;
                    case 7: nc7 = c7 + 1; break;
                    case 8: nc2 = c2 + 3; break;
                    case 9: nc3 = c3 + 2; break;
                }
            }
            ans += dp(w - 1, nc2, nc3, nc5, nc7, !(pre0 && i == 0) && (has0 || i == 0), pre0 && i == 0, false);
        }
    }
    return ans;
    //printf("w = %d, x = %d, c2 = %d, c3 = %d, c5 = %d, c7 = %d, pre0 = %d, lim = %d,   ans = ", w,x,c2,c3,c5,c7,(int)pre0,(int)lim),
        
    //    printf("%lld daze.\n", ans), ans;
}
ll calc(ll x) {
    // printf("\n Calcing %lld\n \n", x);
    static int n, i, c2, c3, c5, c7;
    static ll ans;
    if (x == 0)
        return 0;
    memset(f, -1, sizeof(f));
    for (n = 0; x; x /= 10)
        a[n++] = x % 10;
    --n;
    ans = dp(n, 0, 0, 0, 0, false, true, a[n] == 0);
    rep (i, 1, a[n]) {
        c2 = c3 = c5 = c7 = 0;
        switch (i) {
            case 2: c2 = 1; break;
            case 3: c3 = 1; break;
            case 4: c2 = 2; break;
            case 5: c5 = 1; break;
            case 6: c2 = c3 = 1; break;
            case 7: c7 = 1; break;
            case 8: c2 = 3; break;
            case 9: c3 = 2; break;
        }
        ans += dp(n, c2, c3, c5, c7, false, false, i == a[n]);
    }
    // printf("CALC %lld = %lld\n", x, ans);
    return ans;
}
int main() {
    static ll l, r, t;
    static int i;
    k = io;
    pow3[0] = 1;
    for (i = 1; ; ++i) {
        t = (ll)pow3[i - 1] * 3;
        if (t > k)
            break;
        pow3[i] = t;
    }
    pow5[0] = 1;
    for (i = 1; ; ++i) {
        t = (ll)pow5[i - 1] * 5;
        if (t > k)
            break;
        pow5[i] = t;
    }
    pow7[0] = 1;
    for (i = 1; ; ++i) {
        t = (ll)pow7[i - 1] * 7;
        if (t > k)
            break;
        pow7[i] = t;
    }
    l = io;
    r = io;
    io.print(calc(r - 1) - calc(l - 1));
    //calc(10);

    io.flush();
    return 0;
}
