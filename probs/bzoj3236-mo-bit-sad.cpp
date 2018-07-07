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
    #define crep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define crep(...) if (false)
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define oper operator
#define daze << '\n'
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[30],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p,y;*this>>p;if(c=='.'){*this>>y;for(x=y;x>1;x/=10);if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(std::isnan(x))return*this<<"nan";if(std::isinf(x))return*this<<"inf";if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 100003, M = 1000003;

int mx;
struct BIT {
    int c[N];
    void add(int i, cint v) {
        for (; i <= mx; i += i & -i)
            c[i] += v;
    }
    int query(int i) {
        int res = 0;
        for (; i; i -= i & -i)
            res += c[i];
        return res;
    }
    int query(cint l, cint r) {
        return query(r) - query(l - 1);
    }
} bit0, bit1;
int n, m, a[N], bel[N];
struct Query {
    int l, r, s, t, *ans;
    bool oper < (const Query &rh) const {
        return bel[l] < bel[rh.l] || (bel[l] == bel[rh.l] && r < rh.r);
    }
} qwq[M];
int l, r, cnt[N];
void ins(cint x) {
    if (!cnt[x])
        bit1.add(x, 1);
    ++cnt[x];
    bit0.add(x, 1);
}
void del(cint x) {
    --cnt[x];
    bit0.add(x, -1);
    if (!cnt[x])
        bit1.add(x, -1);
}
int main() {
    static int ans[M][2]; // ******
    io >> n >> m;
    int siz = sqrt((double)n * n / m), c = 0;
    rep (i, 1, n) {
        mx = std::max(mx, a[i] = io);
        bel[i] = bel[i - 1];
        if (++c > siz)
            ++bel[i], c = 1;
    }
    rep (i, 1, m) {
        Query &q = qwq[i];
        io >> q.l >> q.r >> q.s >> q.t;
        q.s = std::max(1, q.s);
        q.t = std::min(mx, q.t);
        q.ans = ans[i];
    }
    std::sort(qwq + 1, qwq + m + 1);
    ins(a[l = r = 1]);
    rep (i, 1, m) {
        const Query &q = qwq[i];
        if (q.s > q.t)
            continue;
        while (l < q.l) del(a[l++]);
        while (l > q.l) ins(a[--l]);
        while (r < q.r) ins(a[++r]);
        while (r > q.r) del(a[r--]);
        q.ans[0] = bit0.query(q.s, q.t);
        q.ans[1] = bit1.query(q.s, q.t);
    }
    rep (i, 1, m)
        io << ans[i][0] << ' ' << ans[i][1] daze;

    return 0;
}
