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

cint N = 500003;

struct Node {
    struct Edge *e;
    int x, d, f, s;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *s, Node *t) : v(t), e(s->e) { s->e = this; }
} pool[N * 2], *curr = pool;
int a1 = 1, a2;
void dfs1(Node *u, Node *fa) {
    if (u->x == 1) {
        Node *v;
        go (e, u->e) if ((v = e->v) != fa) {
            v->d = u->d + 1;
            if (v->x == 1) {
                dfs1(v, u);
                if (v->f >= u->f) u->s = u->f, u->f = v->f; // ****
                else if (v->f > u->s) u->s = v->f;
            } else dfs1(v, u);
        }
        // ccc(u-g ,u->f);
        a1 = std::max(a1, ++u->f + u->s);
    } else if (u->x == 2) {
        Node *v;
        int fi = 0, se = 0;
        go (e, u->e) if ((v = e->v) != fa) {
            v->d = u->d + 1;
            if (v->x == 1) {
                dfs1(v, u);
                if (v->f >= fi) se = fi, fi = v->f;
                else if (v->f > se) se = v->f;
            } else dfs1(v, u);
        }
        a2 = std::max(a2, fi + se + 1);
    } else go (e, u->e) if (e->v != fa) {
        e->v->d = u->d + 1;
        dfs1(e->v, u);
    }
}
void dfs2(Node *u, Node *fa, int f) {
    if (u->x == 2 && fa && fa->x == 1) {
        Node *v;
        int fi = 0;
        go (e, u->e) if ((v = e->v) != fa) {
            dfs2(v, u, 0);
            if (v->x == 1)
                fi = std::max(fi, v->f);
        }
        /* int x = fa->top->f, y = fa->d - fa->top->d + 1;
        if (x == y && x != fa->top->s + 1) y += fa->top->s;
        else y += x - 1;
        if (a2 < 8415 && y + fi + 1 == 8415) {
            ccc(u-g);
        } */
        a2 = std::max(a2, f + fi + 1);
    } else if (u->x == 1) {
        Node *v;
        int fi = 0;
        go (e, u->e) if ((v = e->v) != fa) {
            dfs2(v, u, std::max(f + 1, (v->f + 1 == u->f && u->s + 1 != u->f) ? u->s + 1 : u->f));
            if (v->x == 1)
                fi = std::max(fi, v->f);
        }
    } else
        go (e, u->e) if (e->v != fa) dfs2(e->v, u, 0);
}
int main() {
    int n = io;
    re (i, 1, n) {
        int u, v;
        io >> u >> v;
        new (curr++) Edge(&g[u], &g[v]);
        new (curr++) Edge(&g[v], &g[u]);
    }
    int mi = 1e9;
    rep (i, 1, n) {
        Node &u = g[i];
        io >> u.x;
        if (u.x < mi) mi = u.x;
    }
    if (mi > 1) {
        io << mi << "/1\n";
        return 0;
    }
    dfs1(&g[1], NULL);
    dfs2(&g[1], NULL, 0);
    // 1 / a1 <= 2 / a2
    ccc(a1, a2);
    if (a2 <= 2 * a1) io << "1/" << a1 daze;
    else if (a2 & 1) io << "2/" << a2 daze;
    else io << "1/" << (a2 >> 1) daze;
}
