#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define koishi(e_,u_) for(Edge *e_=(u)_->e;e_;e_=e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
    #define drep(i_,s_,t_) for(int (i_)=(s_);(i_)<=(t_);++(i_))
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define drep(i_,s_,t_) if (false)
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define daze << '\n'
template <cint L>
struct IO{char a[L],b[L],r[30],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}template<class T>IO&operator>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&operator>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x++=0;return*this;}IO&operator>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&operator>>(double&x){int p,y;*this>>p;if(c=='.'){*this>>y;for(x=y;x>1;x/=10);if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>operator T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+L)fwrite(z=b,1,L,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}};template<class T>static d<T>dio(const T x,const int l){return d<T>(x,l);}static d<double>dio(const float x,const int l){return d<double>(x,l);}template<class T>IO&operator<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&operator<<(d<T>x){if(x.x==0)while(x.l--)pc('0');else{if(x.x<0)pc('-'),x.x=-x.x;T y;char*j=r;for(;x.x;x.x=y,--x.l)y=x.x/10,*j++=x.x-y*10+'0';for(;x.l>0;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&operator<<(d<double>x){if(std::isnan(x.x))return*this<<'n'<<'a'<<'n';if(std::isinf(x.x))return*this<<'i'<<'n'<<'f';if(x.x<0)pc('-'),x.x=-x.x;int w=floor(x.x);*this<<w;pc('.');int e=(x.x-w)*pow(10,x.l+1);if(e%10>=5)e/=10,++e;else e/=10;return*this<<d<int>(e,x.l);}IO&operator<<(const float x){return*this<<d<double>(x,6);}IO&operator<<(const double x){return*this<<d<double>(x,6);}IO&operator<<(char*x){while(*x)pc(*x++);return*this;}IO&operator<<(cchar*x){while(*x)pc(*x++);return*this;}IO&operator<<(cchar x){pc(x);return*this;}template<class T>void operator()(T x){*this<<x;}};
IO<1000000> io;

const int N = 403;

int n, a[N * 2], p1[N], p2[N];
int ano(int i) {
    return p1[a[i]] == i ? p2[a[i]] : p1[a[i]];
}
int csn[N], de[N], f[N], g[N], cb[N];
int main() {
    n = io;
    int m = n * 2;
    re (i, 0, m)
        a[i] = io;
    int ans = 0;
    while (true) {
        rep (i, 1, n)
            p1[i] = -1;
        re (i, 0, m) {
            if (p1[a[i]] == -1)
                p1[a[i]] = i;
            else
                p2[a[i]] = i;
        }
        bool ok = true;
        rep (i, 1, n) {
            int pl = p1[i], pr = p2[i];
            if (pl + 1 != pr) {
                ok = false;
                int tl = pl + 1, tr = pr - 1;
                f[pl] = g[pr] = 0;
                int sf = 0, sg = 0;
                rep (j, tl, tr) {
                    int an = ano(j);
                    if (an < pl)
                        sf += 1;
                    if (an > j)
                        sf += -1;
                    if (tl <= an && an < j)
                        sf -= -1;
                    f[j] = sf;
                }
                f[pr] = sf;
                per (j, tr, tl) {
                    int an = ano(j);
                    if (an > pr)
                        sg += 1;
                    if (an < j)
                        sg += -1;
                    if (an > j && an <= tr)
                        sg -= -1;
                    g[j] = sg;
                }
                g[pl] = sg;
                int xx = -10000000;
                re (j, pl, pr)
                    if (f[j] + g[j + 1] > xx)
                        xx = f[j] + g[j + 1], de[i] = j;
                cb[i] = xx;
            } else
                cb[i] = -9999999;
        }
        if (ok)
            break;
        int d = std::max_element(cb + 1, cb + n + 1) - cb;
        if (cb[d] == -9999999)
            break;
        int pl = p1[d], pr = p2[d];
        int t = de[d];
        ans += pr - pl - 1;
        re (j, pl, t)
            std::swap(a[j], a[j + 1]);
        pe (j, pr, t + 1)
            std::swap(a[j], a[j - 1]);
        /*re (j, 0, m)
            io << a[j] <<' ';
        io daze;*/
    }
    io << ans daze;


    return 0;
}
