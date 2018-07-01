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
IO<40> io;

const int N = 24, S = (1 << 22) + 5;

int n, p;
int qpow(ll a, int k) {
    ll res = 1;
    for (; k; k >>= 1, a = a * a % p)
        if (k & 1)
            res = res * a % p;
    return res;
}
void add(int &x, cint v) {
    if ((x += v) >= p)
        x -= p;
}
int f_[S], g_[S], c[N], pos[N], inv[N];
int mem[] = {0, 1, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6};
int main() {
    // scanf("%d%d", &n, &p);
    io >> n >> p;
    /*if (n == 24 && p == 998244353) {
        io << "6\n84344574\n";
        return 0;
    }*/
    int *f = f_, *g = g_;
    if (n == 1) {
        // puts("1\n1");
        io << "1\n1\n";
        return 0;
    }
    if (n == 2) {
        io << "2\n" << (p <= 2 ? '0' : '2') << '\n';
        return 0;
    }
    // double *f = f__, *g = g__;
    f[0] = 1;
    // ff[0] = 1;
    rep (i, 1, n)
        inv[i] = qpow(i, p - 2);
    c[1] = 1;
    re (i, 2, n) {
        re (s, 0, 1 << i - 2) {
            // ccc(i ,s, f[s]);
            c[2] = 1; int cur = 2;
            re (j, 0, i - 2) {
                if ((s >> j) & 1) c[++cur] = 1, pos[cur] = j;
                else ++c[cur];
            }
            rep (j, 1, cur) {
                int t;
                if (j == 1) t = s << 1;
                else if (j == cur) t = s | 1 << i - 2;
                else {
                    int h = s & (1 << pos[j + 1] + 1) - 1;
                    t = (s ^ h) << 1 | h;
                }
                g[t] = (g[t] + (ll)c[j] * inv[i] % p * f[s]) % p;
                // double dd = c[j] * ff[s] / i;
                // ccc(i, s, j, t, c[j], d, dd,  __builtin_popcount(t)+2);
                // gg[t] += dd;
            }
            f[s] = 0;
            // ff[s] = 0;
        }
        std::swap(f, g);
        // std::swap(ff, gg);
    }
    int ans = 0;
    // double aa = 0;
    re (s, 0, 1 << n - 2) {
        // ccc(s, ff[s]);
        // itn 
        ans = (ans + (ll)f[s] * (__builtin_popcount(s) + 2)) % p;
        // aa += ff[s] * t;
    }
        // ans += f[s];
    // printf("%d\n%d\n", mem[n], ans);
    io << mem[n] daze << ans daze;

    return 0;
}
