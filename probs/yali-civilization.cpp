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
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p;*this>>p;if(c=='.'){int y=0,k=0;for(c=gc();isdigit(c);c=gc())y=y*10+(c-'0'),++k;x=(double)y/p_[k-1];if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 500003, LG = 20;

struct Node {
    struct Edge *e;
    Node *f[LG];
    int d, dfn, siz;
} g[N], *vip;
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *s, Node *t) : v(t), e(s->e) { s->e = this; }
} pool[N * 2], *curr = pool;
void arc(Node *u, Node *v) {
    new (curr++) Edge(u, v);
    new (curr++) Edge(v, u);
}
int n, md = 1, lg;
void dfs(Node *u) {
    static int tim = 0;
    u->dfn = ++tim;
    u->siz = 1;
    md = std::max(md, u->d);
    go (e, u->e) if (!e->v->siz) {
        e->v->d = u->d + 1;
        e->v->f[0] = u;
        dfs(e->v);
        u->siz += e->v->siz;
    }
}
void init() {
    for (lg = 0; (1 << lg) <= md; ++lg);
    rep (j, 1, lg) for (Node *u = g + 1; u <= g + n; ++u) if (u->f[j - 1]) u->f[j] = u->f[j - 1]->f[j - 1];
}
const Node *lca(const Node *u, const Node *v) {
    if (u->d < v->d) std::swap(u, v);
    per (j, lg, 0) if (u->f[j] && u->f[j]->d >= v->d) u = u->f[j];
    if (u == v) return u;
    per (j, lg, 0) if (u->f[j] && v->f[j] && u->f[j] != v->f[j]) u = u->f[j], v = v->f[j];
    return u->f[0];
}
const Node *jmp(const Node *u, cint k) {
    per (j, lg, 0) if (k >> j & 1) u = u->f[j];
    return u;
}
struct Range {
    int l, r;
    Range() {}
    Range(cint s, cint t) : l(s), r(t) {}
    bool operator < (const Range &rh) const {
        return l < rh.l || (l == rh.l && r > rh.r);
    }
} a[N], *aend;
void calc(const Node *u) {
    const Node *z = lca(vip, u);
    int dis = vip->d + u->d - 2 * z->d;
    int h = (dis + 1 >> 1) - 1;
    ccc(u-g, vip-g, z-g, dis, h);
    if (u != z && u->d - z->d > h) {
        u = jmp(u, h);
        ccc("jmp1 to ", u-g);
        *aend++ = Range(u->dfn, u->dfn + u->siz - 1);
    } else {
        u = jmp(vip, dis - h - 1);
        ccc("jmp2 to ", u-g);
        if (u->dfn > 1) *aend++ = Range(1, u->dfn - 1);
        if (u->dfn + u->siz <= n) *aend++ = Range(u->dfn + u->siz, n);
    }
}

int main() {
    int m;
    io >> n >> m;
    re (i, 1, n) {
        int u, v;
        io >> u >> v;
        arc(&g[u], &g[v]);
    }
    Node *rt = &g[1];
    rt->d = 1;
    dfs(rt);
    init();
    while (m--) {
        int k = io;
        vip = &g[(int)io];
        aend = a;
        rep (i, 2, k)
            calc(&g[(int)io]);
        std::sort(a, aend);
        int mr = 0, ans = 0;
        for (Range *r = a; r < aend; ++r) {
            ccc(r->l, r->r, mr, ans);
            if (r->r > mr) {
                ans += r->r - std::max(mr + 1, r->l) + 1;
                mr = r->r;
            }
        }
        io << n - ans daze;
    }
}

