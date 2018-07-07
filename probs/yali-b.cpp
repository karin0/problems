#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define go(e_,s_) for(Edge *e_=(s_);e_;e_=e_->e)
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
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p,y;*this>>p;if(c=='.'){*this>>y;for(x=y;x>1;x/=10);if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(std::isnan(x))return*this<<"nan";if(std::isinf(x))return*this<<"inf";if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 100003;

int sz, rr;
struct Node {
    Node *lc, *rc;
    int sum[2];
    Node() {}
    Node(Node *l, Node *r) : lc(l), rc(r) {}
    void uadd(cint qi, cint x, const bool t, cint l = 1, cint r = sz) {
        // ccc(qi, x, l, r);
        if (l == r)
            return (void)(sum[t] += x);
        int mid = l + r >> 1;
        if (qi <= mid) lc->uadd(qi, x, t, l, mid);
        else rc->uadd(qi, x, t, mid + 1, r);
        sum[t] = lc->sum[t] + rc->sum[t];
    }
    void qsum(cint ql, cint qr, const bool t, cint l = 1, cint r = sz) {
        if (ql <= l && r <= qr) 
            return (void)(rr += sum[t]);
        int mid = l + r >> 1;
        if (ql <= mid) lc->qsum(ql, qr, t, l, mid);
        if (qr > mid) rc->qsum(ql, qr, t, mid + 1, r);
    }
} *segt;
Node *build(cint l, cint r) {
    static Node pool[N * 5 * 2 * 2], *curr = pool;
    if (l == r)
        return new (curr++) Node();
    int mid = l + r >> 1;
    return new (curr++) Node(build(l, mid), build(mid + 1, r));
}
int n, m, q, ha[N * 5], *hend, hcnt;
ll a, b, c;
char t[N];
int mod(ll v) {
    return (v %= n) < 0 ? v + n : v;
}
int rk(cint x) {
    return std::lower_bound(ha, hend, x) - ha + 1;
}
int query(int l, int r, const bool i) {
    l = rk(mod(l)); r = rk(mod(r));
    rr = 0;
    if (l > r) segt->qsum(l, sz, i), segt->qsum(1, r, i);
    else segt->qsum(l, r, i);
    return rr;
}
// t[i] != s[p + i]
// s[p+i] = [(ap + ai + b) % n >= c ]
// t = 1: s[p+i] = 0 <-> ap + ai + b \in [0, c - 1]    (mod n)
//            <-> ai + b \in [-ap, c - 1 - ap]         (mod n)
// t = 0: s[p+i] = 1 <-> ap + ai + b \in [c, n - 1]    (mod n)
//            <-> ai + b \in [c-ap, n-1-ap]            (mod n)
struct Query {
    int op, p;
} qwq[N];
int main() {
    io >> n >> a >> b >> c >> m >> t >> q;
    re (i, 0, m) {
        t[i] -= '0';
        ha[hcnt++] = (a * i + b) % n;
    }
    re (i, 0, q) {
        int &p = qwq[i].p;
        io >> qwq[i].op >> p;
        ha[hcnt++] = mod(-a * p);
        ha[hcnt++] = mod(c - 1 - a * p);
        ha[hcnt++] = mod(c - a * p);
        ha[hcnt++] = mod(n - 1 - a * p);
    }
    std::sort(ha, ha + hcnt);
    hend = std::unique(ha, ha + hcnt);
    sz = hend - ha + 1;
    segt = build(1, sz);
    re (i, 0, m) // ***
        segt->uadd(rk((a * i + b) % n), 1, t[i]);
    re (i, 0, q) {
        int p = qwq[i].p;
        if (qwq[i].op == 1)
            io << query(-a * p, c - 1 - a * p, 1) + query(c - a * p, n - 1 - a * p, 0) daze;
        else {
            int x = rk((a * p + b) % n);
            segt->uadd(x, -1, t[p]);
            t[p] ^= 1;
            segt->uadd(x, 1, t[p]);
        }
    }

    return 0;
}
