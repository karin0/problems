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

const int N = 300003;

int sa[N], rk[N], ht[N];
void build(char *s, int n, cint m = CHAR_MAX + 1) {
#define clr(a_, n_) std::fill(a_, a_ + n_, 0)
    static int fir[N], sec[N], cnt[N], tmp[N];
    s[n++] = 0;
    clr(cnt, m);
    re (i, 0, n) ++cnt[s[i]];
    re (i, 1, m) cnt[i] += cnt[i - 1];
    re (i, 0, n) rk[i] = cnt[s[i]] - 1;
    bool uniq = false;
    for (int l = 1; l < n && !uniq; l <<= 1) {
        re (i, 0, n) fir[i] = rk[i], sec[i] = i + l < n ? rk[i + l] : 0;
        clr(cnt, n);
        re (i, 0, n) ++cnt[sec[i]];
        re (i, 1, n) cnt[i] += cnt[i - 1];
        per (i, n - 1, 0) tmp[--cnt[sec[i]]] = i;
        clr(cnt, n);
        re (i, 0, n) ++cnt[fir[i]];
        re (i, 1, n) cnt[i] += cnt[i - 1];
        per (i, n - 1, 0) sa[--cnt[fir[tmp[i]]]] = tmp[i];
        rk[sa[0]] = 0;
        uniq = true;
        for (int i = 1; i < n; ++i) {
            rk[sa[i]] = rk[sa[i - 1]];
            if (fir[sa[i]] == fir[sa[i - 1]] && sec[sa[i]] == sec[sa[i - 1]]) uniq = false;
            else ++rk[sa[i]];
        }
    }
    --n;
    for (int k = 0, i = 0; i < n; ++i) {
        // if (!rk[i]) continue;
        if (k) --k;
        for (int j = sa[rk[i] - 1]; s[i + k] == s[j + k]; ++k);
        ht[rk[i]] = k;
    }
}
int n, a[N], p[N];
ll f[N], g[N];
char s[N];
template <class T> void cmx(T &x, const T v) { x = std::max(x, v); }
template <class T> void cmn(T &x, const T v) { x = std::min(x, v); }
int fa[N], mn[N], mx[N], sz[N];
void init() {
    re (i, 0, n) {
        fa[i] = i;
        sz[i] = 1;
        mn[i] = mx[i] = a[i];
    }
}
int find(cint x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void unite(cint x, cint y) {
    // x = find(x); y = find(y);
    sz[x] += sz[y];
    cmn(mn[x], mn[y]);
    cmx(mx[x], mx[y]);
    fa[y] = x;
}
bool cmp(cint i, cint j) { return ht[i] > ht[j]; }
int main() {
    io >> n >> s;
    build(s, n);
    re (i, 0, n)
        io >> a[i];
    rep (i, 1, n)
        p[i] = i;
    // rep (i, 0, n) ccc(i, s[i], sa[i], sa[i - 1], ht[i], s);
    std::sort(p + 1, p + n + 1, cmp);
    std::fill(g, g + n, LLONG_MIN);
    init();
    rep (i, 1, n) {
        cint x = p[i];
        // ccc(i, x, ht[x]);
        if (x <= 1) continue;
        cint fx = find(sa[x]), fy = find(sa[x - 1]);
        if (fx == fy) continue;
        // if (ht[x] != ht[x - 1]) continue;
        f[ht[x]] += (ll)sz[fx] * sz[fy];
        cmx(g[ht[x]], std::max((ll)mx[fx] * mx[fy], (ll)mn[fx] * mn[fy]));
        unite(fx, fy);
    }
    per (i, n - 2, 0)
        f[i] += f[i + 1], cmx(g[i], g[i + 1]);
    re (i, 0, n)
        io << f[i] << ' ' << (f[i] ? g[i] : 0) << '\n';

    return 0;
}
