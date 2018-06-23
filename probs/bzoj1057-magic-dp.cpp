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
#define desu << '\n'
struct IO{static cint L=1000000;char a[L],b[L],r[30],*s,*t,*z,*j,c;bool f;IO():z(b){}~IO(){fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}template<class T>IO&operator>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());if((f=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&operator>>(char*q){for(c=gc();!isgraph(c);c=gc());*q++=c;for(c=gc();isgraph(c);*q++=c,c=gc());*q++=0;return*this;}IO&operator>>(char&q){for(q=gc();!isgraph(q);q=gc());return*this;}template<class T>operator T(){T x;*this>>x;return x;}void pc(cchar q){if(z==b+L)fwrite(z=b,1,L,stdout);*z++=q;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>IO&operator<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;for(j=r;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}IO&operator<<(cchar*q){while(*q)pc(*q++);return*this;}IO&operator<<(cchar q){pc(q);return*this;}}io;

const int N = 2001;

int sq(const int x) { return x * x; }
int n, m, fl[N][N], fr[N][N];
char a[N][N];
int main() {
    static int i, j, rect = 1, squa = 1, al, ar, h;
    io >> n >> m;
    rep (i, 1, n) rep (j, 1, m)
        io >> a[i][j];
    rep (i, 1, n) {
        fl[i][1] = 1;
        rep (j, 2, m)
            fl[i][j] = a[i][j] != a[i][j - 1] ? fl[i][j - 1] + 1 : 1;
        fr[i][m] = 1;
        per (j, m - 1, 1)
            fr[i][j] = a[i][j] != a[i][j + 1] ? fr[i][j + 1] + 1 : 1;
    }
    rep (j, 1, m) {
        rep (i, 1, n) {
            using std::min;
            using std::max;
            if (i == 1 || a[i][j] == a[i - 1][j])
                al = fl[i][j], ar = fr[i][j], h = 1;
            else
                al = min(al, fl[i][j]), ar = min(ar, fr[i][j]), ++h;
            rect = max(rect, h * (al + ar - 1));
            squa = max(squa, sq(min(h, al + ar - 1)));
        }
    }
    io << squa desu << rect desu;

    return 0;
}


