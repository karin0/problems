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
const int p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint L>struct IO{char a[L],b[L],r[30],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}template<class T>IO&operator>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&operator>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x++=0;return*this;}IO&operator>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&operator>>(double&x){int p,y;*this>>p;if(c=='.'){*this>>y;for(x=y;x>1;x/=10);if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>operator T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+L)fwrite(z=b,1,L,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;cint l;d(const T x_,cint l_):x(x_),l(l_){}operator T&(){return x;}};template<class T>static d<T>dio(const T x,cint l){return d<T>(x,l);}template<class T>IO&operator<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&operator<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;int l_=x.l;for(;x;x.x=y,--l_)y=x/10,*j++=x-y*10+'0';for(;l_>0;pc('0'),--l_);while(j!=r)pc(*--j);}return*this;}IO&operator<<(d<double>x){if(std::isnan(x))return*this<<'n'<<'a'<<'n';if(std::isinf(x))return*this<<'i'<<'n'<<'f';if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&operator<<(const double x){return*this<<d<double>(x,6);}IO&operator<<(char*x){while(*x)pc(*x++);return*this;}IO&operator<<(cchar*x){while(*x)pc(*x++);return*this;}IO&operator<<(cchar x){return pc(x),*this;}template<class T>void operator()(T x){*this<<x;}};
IO<1000000> io;

const int N = 100003;

int n;
int main() {
    io >> n;
    int m = io;
    while (m--) {
        
    }

    return 0;
}


