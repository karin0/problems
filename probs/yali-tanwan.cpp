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
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}char*gs(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return x+1;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p;*this>>p;if(c=='.'){int y=0,k=0;for(c=gc();isdigit(c);c=gc())y=y*10+(c-'0'),++k;x=(double)y/p_[k-1];if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 50002, M = 500;
int n, m, qc;
ll f[M], h[M], ans[N];
struct Limit {
    int l, r;
} ra[N];
int sub(cint x) {
    return x < 0 ? x + m : x;
}
struct Item {
    int w, v;
    Item() {}
    Item(cint a, cint b) : w(a), v(b) {}
};
struct Node {
    Node *lc, *rc;
    std::vector<Item> a;
    ll g[M];
    Node() {}
    Node(Node *l, Node *r) : lc(l), rc(r) {}
    void ins(cint ql, cint qr, const Item &x, cint l = 1, cint r = qc) {
        if (ql <= l && r <= qr)
            return a.push_back(x);
        int mid = l + r >> 1;
        if (ql <= mid) lc->ins(ql, qr, x, l, mid);
        if (qr > mid) rc->ins(ql, qr, x, mid + 1, r);
    }
    void dfs(cint l = 1, cint r = qc) {
        re (i, 0, m)
            g[i] = f[i];
        for (auto &x : a) {
            re (i, 0, m)
                h[i] = f[i];
            re (i, 0, m) {
                ll t = h[sub(i - x.w)];
                if (t >= 0)
                    f[i] = std::max(h[i], t + x.v);
            }
        }
        if (lc) {
            int mid = l + r >> 1;
            lc->dfs(l, mid);
            rc->dfs(mid + 1, r);
        } else {
            ll &rr = ans[l];
            int tl = ra[l].l, tr = ra[l].r;
            ccc(l);
            rep (i, tl, tr)
                rr = std::max(rr, f[i]);
        }
        re (i, 0, m)
            f[i] = g[i];
    }
} *segt;
Node *build(cint l, cint r) {
    static Node pool[N * 2], *curr = pool;
    if (l == r) return new (curr++) Node;
    int mid = l + r >> 1;
    return new (curr++) Node(build(l, mid), build(mid + 1, r));
}
template <class T, int S>
struct Deque {
    T a[S * 2], *l, *r;
    Deque() : l(a + S), r(a + S) {}
    T *push_back(const T &x) { *--l = x; return l; }
    T *push_front(const T &x) { *r++ = x; return r - 1; }
    T pop_back() { return *l++; }
    T pop_front() { return *--r; }
};
struct Query {
    Item x;
    int l;
} *rec[N], **rl = rec, **rr = rec;
Deque<Query, N> dq;
struct Coverage {
    Query x;
    int r;
    Coverage() {}
    Coverage(const Query &a, cint b) : x(a), r(b) {}
} qwq[N], *cr = qwq;
int main() {
    io >> n >> m;
    rep (i, 1, n) {
        static char s[5];
        io >> s;
        if (s[0] == 'Q') {
            ans[++qc] = -1;
            io >> ra[qc].l >> ra[qc].r;
            // ccc(qc, ra[qc].l, ra[qc].r);
            for (Query **p = rl; p < rr; ++p)
                (*p)->l = qc;
            rl = rr;
        } else if (s[0] == 'I') {
            Query x;
            io >> x.x.w >> x.x.v;
            x.x.w %= m;
            *rr++ = s[1] == 'F' ? dq.push_front(x) : dq.push_back(x);
        } else
            *cr++ = Coverage(s[1] == 'F' ? dq.pop_front() : dq.pop_back(), qc);
    }
    segt = build(1, qc);
    for (Coverage *p = qwq; p < cr; ++p) if (p->x.l)
        segt->ins(p->x.l, p->r, p->x.x);
    for (Query *p = dq.l; p < dq.r; ++p) if (p->l)
        segt->ins(p->l, qc, p->x);
    re (i, 1, m)
        f[i] = -1;
    segt->dfs();
    rep (i, 1, qc)
        io << ans[i] daze;
}
