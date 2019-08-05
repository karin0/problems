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
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1> io;

cint N = 102;
const double eps = 1e-8, inf = 1e9;

struct MCMF {
    int n;
    struct Edge;
    struct Node {
        struct Edge *e, *p;
        double d;
        int f;
        bool inq;
    } g[N + N], *s, *t;
    struct Edge {
        Node *u, *v;
        Edge *e, *r;
        int c;
        double w;
        Edge() {}
        Edge(Node *u_, Node *v_, int c_, double w_) : u(u_), v(v_), e(u_->e), c(c_), w(w_) { u->e = this; }
    } pool[(N * N + N + N) * 2], *curr;
    MCMF() : curr(pool) {}
    Node &operator [] (cint i) {
        return g[i];
    }
    void reset() {
        for (Node *u = g + 1; u <= g + n; ++u)
            u->e = NULL;
        curr = pool;
    }
    void arc(Node *u, Node *v, cint c, const double w) {
        new (curr++) Edge(u, v, c, w);
        new (curr++) Edge(v, u, 0, -w);
        (u->e->r = v->e)->r = u->e;
    }
    double operator () () {
        static std::queue<Node *> q;
        double res = 0;
        while (true) {
            for (Node *u = g + 1; u <= g + n; ++u) {
                u->p = NULL;
                u->f = 0;
                u->d = inf;
                u->inq = false;
            }
            s->f = INT_MAX;
            s->d = 0;
            s->inq = true;
            q.push(s);
            while (!q.empty()) {
                Node *u = q.front();
                q.pop();
                u->inq = false;
                go (e, u->e) if (e->c && e->v->d > u->d + e->w) {
                    Node *v = e->v;
                    v->d = u->d + e->w;
                    v->p = e;
                    v->f = std::min(u->f, e->c);
                    if (!v->inq) {
                        v->inq = true;
                        q.push(v);
                    }
                }
            }
            if (t->d >= inf) break;
            for (Edge *e = t->p; e; e = e->u->p) {
                e->c -= t->f;
                e->r->c += t->f;
            }
            res += t->f * t->d;
        }
        return res;
    }
} g;
int n, a[N][N], b[N][N];
bool check(const double x) {
    rep (i, 1, n) {
        g.arc(g.s, &g[i], 1, 0);
        g.arc(&g[n + i], g.t, 1, 0);
        rep (j, 1, n)
            g.arc(&g[i], &g[n + j], 1, x * b[i][j] - a[i][j]);
    }
    // double t = -g();
    bool res = g() <= 0;
    // ccc(x, t);
    g.reset();
    return res;
}
int main() {
    io >> n;
    g.n = n * 2 + 2;
    g.s = &g[g.n];
    g.t = &g[g.n - 1];
    rep (i, 1, n) rep (j, 1, n)
        io >> a[i][j];
    rep (i, 1, n) rep (j, 1, n)
        io >> b[i][j];
    double l = 0, r = 1e6;
    while (fabs(r - l) > eps) {
        double x = (l + r) / 2;
        (check(x) ? l : r) = x;
    }
    printf("%.6f\n", l);
}
