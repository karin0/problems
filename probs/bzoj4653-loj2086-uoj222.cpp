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
struct IO{static cint L=1000000;char a[L],b[L],r[30],*s,*t,*z;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}template<class T>IO&operator>>(T&x){char c=gc();for(;c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&operator>>(char*x){char c=gc();for(;!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x++=0;return*this;}IO&operator>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}template<class T>operator T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+L)fwrite(z=b,1,L,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}};template<class T>static d<T>dio(const T x,const int l){return d<T>(x,l);}template<class T>IO&operator<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j;for(j=r;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&operator<<(d<T>x){if(x.x==0)while(x.l--)pc('0');else{if(x.x<0)pc('-'),x.x=-x.x;T y;char*j;for(j=r;x.x;x.x=y,--x.l)y=x.x/10,*j++=x.x-y*10+'0';for(;x.l>0;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&operator<<(d<double>x){if(x.x<0)pc('-'),x.x=-x.x;int w=floor(x.x);*this<<w;pc('.');int e=(x.x-w)*pow(10,x.l+1);if(e%10>=5)e/=10,++e;else e/=10;return*this<<d<int>(e,x.l);}IO&operator<<(cchar*x){while(*x)pc(*x++);return*this;}IO&operator<<(cchar x){pc(x);return*this;}}io;

const int N = 500002, M = 200002;

int mx, res;
struct Node {
    Node *lc, *rc;
    int max, tag;
    Node() {}
    Node(Node *l, Node *r) : lc(l), rc(r) { maintain(); }
    void maintain() { max = std::max(lc->max, rc->max); }
    void push_down() { if (tag) lc->cover(tag), rc->cover(tag), tag = 0; }
    void cover(cint v) { max += v; tag += v; }
    void uadd(cint ql, cint qr, cint l = 1, cint r = mx) {
        if (ql <= l && r <= qr)
            return cover(1);
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->uadd(ql, qr, l, mid);
        if (qr > mid)
            rc->uadd(ql, qr, mid + 1, r);
        maintain();
    }
    void usub(cint ql, cint qr, cint l = 1, cint r = mx) {
        if (ql <= l && r <= qr)
            return cover(-1);
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->usub(ql, qr, l, mid);
        if (qr > mid)
            rc->usub(ql, qr, mid + 1, r);
        maintain();
    }
    void qmax(cint ql, cint qr, cint l = 1, cint r = mx) {
        if (ql <= l && r <= qr)
            return (void)(res = std::max(res, max));
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->qmax(ql, qr, l, mid);
        if (qr > mid)
            rc->qmax(ql, qr, mid + 1, r);
    }
} *segt;
Node *build(cint l, cint r) {
    static Node pool[N * 4], *curr = pool; // that's not wrong.
    if (l == r)
        return curr++;
    int mid = (l + r) >> 1;
    return new (curr++) Node(build(l, mid), build(mid + 1, r));
}
int qmax() { res = 0; segt->qmax(1, mx); return res; }
struct Range {
    int l, r, len;
    bool operator < (const Range &rh) const {
        return len < rh.len;
    }
} a[N];
int s[N * 2];
int main() {
    int n, m, c = 0;
    io >> n >> m;
    rep (i, 1, n) {
        Range &q = a[i];
        io >> q.l >> q.r;
        s[++c] = q.l; s[++c] = q.r;
        q.len = q.r - q.l;
    }
    std::sort(a + 1, a + n + 1);
    std::sort(s + 1, s + c + 1);
    int *ed = std::unique(s + 1, s + c + 1);
    mx = ed - 1 - s;
    rep (i, 1, n) {
        Range &q = a[i];
        q.l = std::lower_bound(s + 1, ed, q.l) - s;
        q.r = std::lower_bound(s + 1, ed, q.r) - s;
    }
    segt = build(1, mx);
    int ans = INT_MAX;
    for (int l = 1, r = 1; r <= n; ++r) {
        Range &q = a[r];
        segt->uadd(q.l, q.r);
        while (l <= r && qmax() >= m) {
            // ccc(l, r);
            ans = std::min(ans, q.len - a[l].len);
            segt->usub(a[l].l, a[l].r);
            ++l;
        }
    }
    // ccc(mx);
    if (ans >= INT_MAX)
        io << '-' << '1' daze;
    else
        io << ans daze;
    return 0;
}
