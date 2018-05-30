#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define ccf(x) std::cerr << #x " = " << x << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);/*p=b;*/}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;/*return s==t?EOF:*s++;*/}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,const char end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;
typedef long long ll;

const int N = 666003, mo = 998244353, pr = 3;
int qpow(ll x, ll n) {
    static ll res;
    for (res = 1; n; n >>= 1, x = x * x % mo)
        if (n & 1)
            res = res * x % mo;
    return res;
}
int mck(int x) {
    return x >= mo ? x - mo : x;
}
int mck2(int x) {
    return x < 0 ? x + mo : x;
}
template <class T>
void qfill(T *l, T *r, T v) {
    if (l < r)
        std::fill(l, r, v);
}
namespace ntt {
    ll w[N], wi[N], ni;  // ni as ll;
    int n, rev[N];
    void init(const int _n) {
        static int i, k, x, xi;
        n = _n;
        for (k = 0, x = 1; x < n; x <<= 1, ++k);
        ni = qpow(n, mo - 2);
        x = qpow(pr, (mo - 1) / n);
        xi = qpow(x, mo - 2);
        w[0] = wi[0] = 1;
        re (i, 1, n) {
            w[i] = w[i - 1] * x % mo;
            wi[i] = wi[i - 1] * xi % mo;
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        }
    }
    void dft(int *a) {
        static int i, l, m, t, x, *p;
        re (i, 0, n)
            if (i < rev[i])
                std::swap(a[i], a[rev[i]]);
        for (l = 2; l <= n; l <<= 1) {
            m = l >> 1;
            t = n / l;
            for (p = a; p != a + n; p += l)
                re (i, 0, m) {
                    x = w[t * i] * p[m + i] % mo;
                    p[m + i] = mck2(p[i] - x);
                    p[i] = mck(p[i] + x);
                }
        }
    }
    void idft(int *a) {
        static int i;
        std::swap(w, wi);
        dft(a);
        std::swap(w, wi);
        re (i, 0, n)
            a[i] = a[i] * ni % mo;
    }
}
void pmul(int *a, int *b, const int n) {
    static int i;
    ntt::init(n);
    ntt::dft(a);
    ntt::dft(b);
    re (i, 0, n)
        a[i] = (ll)a[i] * b[i] % mo;
    ntt::idft(a);
}
ll fac[N], faci[N], inv[N];
int expand(const int n) {
    static int l;
    for (l = 1; l < n; l <<= 1);
    return l;
}
void pinv(const int *a, const int n, int *b) {
    static int t[N];
    if (n == 1) {
        b[0] = qpow(a[0], mo - 2);
        return;
    }
    pinv(a, n >> 1, b);
    int l = n << 1, i;
    std::copy(a, a + n, t);
    qfill(t + n, t + l, 0);
    qfill(b + n, b + l, 0);  // ?????
    ntt::init(l);
    ntt::dft(t);
    ntt::dft(b);
    re (i, 0, l)
        b[i] = (ll)b[i] * mck2(2 - (ll)t[i] * b[i] % mo) % mo;
    ntt::idft(b);
    qfill(b + n, b + l, 0);  // ?????
}
void pdiff(int *a, int n) {
    static int i;
    re (i, 0, n - 1)
        a[i] = (ll)a[i + 1] * (i + 1) % mo;
    a[n - 1] = 0;
}
void pintg(int *a, int n) {
    static int i;
    per (i, n - 1, 1)
        a[i] = a[i - 1] * inv[i] % mo;
    a[0] = 0;
}
void pln(int *a, int n) {
    static int t[N], l;
    l = n << 1;
    // ccc("plning");
    // ccf(n);
    pinv(a, n, t);
    /*int i;
    re (i, 0, l) {
        ccc("pinv: ");
        ccc(i), ccf(a[i]);
    }*/
    pdiff(a, n);
    // ccf("will mul");
    qfill(a + n, a + l, 0);
    qfill(t + n, t + l, 0);
    // ccf("filled");
    pmul(a, t, l);
    pintg(a, n);
}
void dac(const int l, const int r, const int *a, int *res) {
    if (l == r) {
        res[0] = 1;
        res[1] = a[l];
        return;
    }
    int mid = (l + r) >> 1, p = expand(r - l + 2);
    dac(l, mid, a, res);
    qfill(res + mid - l + 2, res + p, 0);
    int *t = new int[p]; // using a global one as temp array causes trouble.
    dac(mid + 1, r, a, t);
    qfill(t + r - mid + 1, t + p, 0);
    pmul(res, t, p);
    qfill(res + r - l + 2, res + p, 0);
    // delete[] t;
    /* re (i, 0, p) {
        ccc(l);
        ccc(r);
        ccc(i);
        ccf(res[i]);
    } */
}
void calc(const int *a, const int n, const int l, int *res) { // l = expand(t + 1)
    static int i;
    // ccf(n);
    // ccf(l);
    dac(1, n, a, res);
    //ccf("daced");
    qfill(res + n + 1, res + l, 0);
    /*re (i, 0, l) {
        ccc("dac: ");
        ccf(res[i]);
    }*/
    pln(res, l);
    /*re (i, 0, l) {
        ccc("ln: ");
        ccf(res[i]);
    }*/
    re (i, 1, l) {
        res[i] = (ll)res[i] * i % mo * faci[i] % mo;
        if ((i & 1) == 0)
            res[i] = mck(mo - res[i]);
        //ccc(i), ccf(res[i] * fac[i] % mo);
    }
    res[0] = n;
}
int main() {
    static int i, n, m, l, t, u, a[N], b[N], a1[N], b1[N], nmi;
    // scanf("%d%d", &n, &m);
    /*n = 8;
    rep (i, 1, n)
        a[i] = i;
    fac[0] = faci[0] = fac[1] = faci[1] = inv[1] = 1;
    rep (i, 2, 5000) {
        inv[i] = (mo - mo / i) * inv[mo % i] % mo;
        fac[i] = fac[i - 1] * i % mo;
        faci[i] = faci[i - 1] * inv[i] % mo;
    }
    calc(a, n, 16, a1);
    return 0;*/
    n = io;
    m = io;
    rep (i, 1, n)
        /*scanf("%d", &a[i]); */a[i] = io;
    rep (i, 1, m)
        /* scanf("%d", &b[i]); */ b[i] = io;
    t = io;
    //ccf(t);
    u = expand(t + 1); // ****
    //ccf(u);
    fac[0] = faci[0] = fac[1] = faci[1] = inv[1] = 1;
    rep (i, 2, u * 2) {
        inv[i] = (mo - mo / i) * inv[mo % i] % mo;
        fac[i] = fac[i - 1] * i % mo;
        faci[i] = faci[i - 1] * inv[i] % mo;
    }
    //ccf(n);
    //ccf(m);
    calc(a, n, u, a1);
    calc(b, m, u, b1);
    l = u << 1;
    std::fill(a1 + u, a1 + l, 0);
    std::fill(b1 + u, b1 + l, 0);
    pmul(a1, b1, l);
    nmi = qpow((ll)n * m, mo - 2);  // ****
    rep (i, 1, t)
        io.print((int)(a1[i] * fac[i] % mo * nmi % mo));

    return 0;
}
