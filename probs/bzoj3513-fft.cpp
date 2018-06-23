#include <bits/stdc++.h>
#define rep(i_,s_,t_) for((i_)=(s_);(i_)<=(t_);++(i_))
#define re(i_,s_,t_) for((i_)=(s_);(i_)<(t_);++(i_))
#define per(i_,s_,t_) for((i_)=(s_);(i_)>=(t_);--(i_))
#define pe(i_,s_,t_) for((i_)=(s_);(i_)>(t_);--(i_))
#define koishi(e_,u_) for(Edge *e_=(u)_->e;e_;e_=e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define daze << '\n'
struct IO{static cint L=1000000;char a[L],b[L],r[30],*s,*t,*z;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}template<class T>IO&operator>>(T&x){char c=gc();for(;c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&operator>>(char*q){char c=gc();for(;!isgraph(c);c=gc());*q++=c;for(c=gc();isgraph(c);*q++=c,c=gc());*q++=0;return*this;}IO&operator>>(char&q){for(q=gc();!isgraph(q);q=gc());return*this;}template<class T>operator T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+L)fwrite(z=b,1,L,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct dio_t{T x;int l;dio_t(const T x_,cint l_):x(x_),l(l_){}};template<class T>static dio_t<T>dio(const T x,const int l){return dio_t<T>(x,l);}template<class T>IO&operator<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j;for(j=r;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&operator<<(dio_t<T>x){if(x.x==0)while(x.l--)pc('0');else{if(x.x<0)pc('-'),x.x=-x.x;T y;char*j;for(j=r;x.x;x.x=y,--x.l)y=x.x/10,*j++=x.x-y*10+'0';for(;x.l>0;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&operator<<(dio_t<double>x){if(x.x<0)pc('-'),x.x=-x.x;int w=floor(x.x);*this<<(w=floor(x.x));pc('.');int e=(x.x-w)*pow(10,x.l+1);if(e%10>=5)e/=10,++e;else e/=10;return*this<<dio_t<int>(e,x.l);}IO&operator<<(cchar*x){while(*x)pc(*x++);return*this;}IO&operator<<(cchar x){pc(x);return*this;}}io;

const int N = 263333;
const double tau = 2 * acos(-1);

struct comp {
    double r, i;
    comp() {}
    comp(double _r, double _i) : r(_r), i(_i) {}
    comp conj() const { return comp(r, -i); }
    comp operator + (const comp &b) const { return comp(r + b.r, i + b.i); }
    comp operator - (const comp &b) const { return comp(r - b.r, i - b.i); }
    comp operator * (const comp &b) const { return comp(r * b.r - i * b.i, i * b.r + r * b.i); }
};
namespace fft {
    comp w[N], wi[N];
    int rev[N], n, i, k, m, l, t;
    void init(const int n_) {
        static double a;
        for (k = 0, n = 1; n < n_; ++k, n <<= 1);
        re (i, 0, n) {
            a = tau / n * i;
            w[i] = comp(cos(a), sin(a));
            wi[i] = w[i].conj();
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
        }
    }
    void dft(comp *a, const comp *w = fft::w) {
        static comp x, *p;
        re (i, 0, n)
            if (i > rev[i])
                std::swap(a[i], a[rev[i]]);
        for (l = 2; l <= n; l <<= 1) {
            m = l >> 1;
            t = n / l;
            for (p = a; p != a + n; p += l) {
                re (i, 0, m) {
                    x = w[t * i] * p[m + i];
                    p[m + i] = p[i] - x;
                    p[i] = p[i] + x;
                }
            }
        }
    }
    void idft(comp *a) {
        dft(a, wi);
        re (i, 0, n)
            a[i].r /= n;
    }
};
int i;
void sq(comp *a, int n) {
    fft::init(n);
    fft::dft(a);
    n = fft::n;
    re (i, 0, n)
        a[i] = a[i] * a[i];
    fft::idft(a);
}

comp p[N];
ll cnt[N], f[N], ss, tt;
int main() {
    static int ks, n, x, mx;
    io >> ks;
    while (ks--) {
        io >> n;
        re (i, 0, n) {
            io >> x;
            mx = std::max(mx, x);
            ++cnt[x];
            --f[x * 2];
        }
        rep (i, 1, mx)
            p[i].r = cnt[i];
        /* rep (i, 1, mx)
            ccc(i, p[i].r, p[i].i); */
        sq(p, mx << 1);
        per (i, mx - 1, 1)
            cnt[i] += cnt[i + 1];
        tt = ss = (ll)n * (n - 1) * (n - 2) / 6;
        rep (i, 1, mx)
            tt -= ((f[i] + (ll)round(p[i].r)) >> 1) * cnt[i];
        io << IO::dio((double)tt / ss, 7) daze;

        if (ks) {
            rep (i, 1, mx)
                cnt[i] = 0;
            mx <<= 1;
            rep (i, 2, mx)
                f[i] = 0;
            mx = fft::n; // ****
            re (i, 0, mx)
                p[i] = comp(0, 0);
            mx = 0;
        }
    }

    return 0;
}
