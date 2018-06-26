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

const int N = 5001;

struct Pos {
    int x, y;
    Pos() {}
    Pos(cint i, cint j) : x(i), y(j) {}
    bool operator < (const Pos &rh) const {
        return x <= rh.x && y <= rh.y;
    }
} p[N * N];
int t[N * N], n, m, q, siz;
ll a, b, c, d, h;
int main() {
    io >> h >> a >> b >> c >> d >> n >> m >> q;
    if (n + m == 2)
        return (io << '1' << '\n'), 0;
    siz = n * m;
    rep (i, 1, siz)
        t[i] = i;
    rep (i, 1, siz) {
        h = ((a * h + b) % d * h + c) % d;
        std::swap(t[i], t[h % i + 1]);
    }
    while (q--)
        std::swap(t[(int)io], t[(int)io]);
    int x = 1, y = 1;
    rep (i, 1, siz) {
        p[t[i]] = Pos(x, y);
        ccc(i, x, y, t[i]);
        if (++y > m) ++x, y = 1;
    }
    Pos c1, c2;
    c1 = c2 = p[1];
    int cnt = 1;
    io << '1' << ' ';
    ccc(1, c1.x, c1.y, c2.x, c2.y);
    rep (i, 2, siz) {
        if (p[i] < c1)
            c1 = p[i];
        else if (c2 < p[i])
            c2 = p[i];
        else if (c1 < p[i] && p[i] < c2)
            23333;
        else
            continue;
        ccc(i, c1.x, c1.y, c2.x, c2.y);
        io << i;
        if (++cnt == n + m - 1)
            return (io << '\n'), 0;
        io << ' ';
    }
    
    return 0;
}
