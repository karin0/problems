#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define go(e_,s_) for(Edge *e_=s_;e_;e_=e_->e)
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
IO<1000000, 10> io;

cint N = 1120, inf = INT_MAX;
struct G { // 有源汇带上下界最小流
    int n;
    struct Edge;
    struct Node {
        struct Edge *e, *c;
        int d, x;
    } g[N], *s, *t, *ps, *pt;
    struct Edge {
        Node *v;
        int c;
        Edge *e, *r;
        Edge() {}
        Edge(Node *u_, Node *v_, cint c_) : v(v_), c(c_), e(u_->e) { u_->e = this; }
    } pool[N * N * 2], *curr;
    G() : curr(pool) {}
    Node &operator [] (cint i) {
        return g[i];
    }
    Edge *arc(Node *u, Node *v, cint c) {
        Edge *e = new (curr++) Edge(u, v, c);
        new (curr++) Edge(v, u, 0);
        return (e->r = v->e)->r = e;
    }
    Edge *arc(Node *u, Node *v, cint lb, cint ub) {
        Edge *e = arc(u, v, ub - lb);
        u->x -= lb;
        v->x += lb;
        return e;
    }
    bool bfs() {
        std::queue<Node *> q;
        rep (i, 1, n)
            g[i].c = g[i].e, g[i].d = 0;
        q.push(s);
        s->d = 1;
        while (!q.empty()) {
            Node *u = q.front(), *v;
            q.pop();
            go (e, u->e) if (e->c > 0 && !(v = e->v)->d) {
                v->d = u->d + 1;
                if (v == t) return true;
                q.push(v);
            }
        }
        return false;
    }
    int dfs(Node *u, int lim) {
        if (u == t || lim == 0)
            return lim;
        int f, res = 0;
        for (Edge *&e = u->c; e; e = e->e) if (e->c > 0 && e->v->d == u->d + 1 && (f = dfs(e->v, std::min(e->c, lim))) > 0) {
            res += f;
            lim -= f;
            e->c -= f;
            e->r->c += f;
            if (!lim) return res;
        }
        return res;
    }
    void dinic() {
        for (; bfs(); dfs(s, inf));
    }
    int solve() {
        rep (i, 1, n) {
            Node &u = g[i];
            if (u.x > 0) arc(s, &u, u.x);
            else if (u.x < 0) arc(&u, t, -u.x);
        }
        dinic();
        Edge *e = arc(pt, ps, inf);
        dinic();
        return e->r->c;
    }
    void init(cint m) {
        n = m + 4;
        ps = &g[m + 1];
        pt = ps + 1;
        s = pt + 1;
        t = s + 1;
        // ccc(n, m, ps-g, pt-g, s-g, t-g);
    }
} g;

int main() {
    int n = io;
    g.init(n);
    rep (i, 1, n) {
        int k = io;
        G::Node *u = &g[i];
        g.arc(g.ps, u, inf);
        if (k) rep (j, 1, k)
            g.arc(u, &g[(int)io], 1, inf);
        else g.arc(u, g.pt, inf);
    }
    io << g.solve() daze;

    return 0;
}
