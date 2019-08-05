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
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}char*gs(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return x+1;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 502, M = 100002;

struct Network {
    int n;
    struct Edge;
    struct Node {
        int d;
        struct Edge *e, *c;
    } g[N * 2], *s, *t;
    struct Edge {
        Node *v;
        ll c;
        Edge *e, *r;
        Edge() {}
        Edge(Node *s, Node *t, cll x) : v(t), c(x), e(s->e) { s->e = this; }
    } pool[M * 4], *curr;
    Network() : curr(pool) {}
    Node &operator [] (cint i) {
        return g[i];
    }
    void arc(Node *u, Node *v, cll c) {
        ccc(u-g, v-g, c);
        new (curr++) Edge(u, v, c);
        new (curr++) Edge(v, u, 0);
        (u->e->r = v->e)->r = u->e;
    }
    void arc(cint u, cint v, cll c) {
        arc(&g[u], &g[v], c);
    }
    bool bfs() {
        for (Node *u = g + 1; u <= g + n; ++u)
            u->d = 0, u->c = u->e;
        s->d = 1;
        std::queue<Node *> q;
        q.push(s);
        while (!q.empty()) {
            Node *u = q.front(), *v;
            ccc(u-g);
            q.pop();
            go (e, u->e) if (e->c && !(v = e->v)->d) {
                v->d = u->d + 1;
                if (v == t) return true;
                q.push(v);
            }
        }
        return false;
    }
    ll dfs(Node *u, ll l) {
        ccc(u-g, l);
        if (u == t || !l) return l;
        cll ol = l;
        ll f;
        for (Edge *&e = u->c; e; e = e->e) if (e->c && e->v->d == u->d + 1 && (f = dfs(e->v, std::min(e->c, l)))) {
            l -= f;
            e->c -= f;
            e->r->c += f;
            if (!l) return ol;
        }
        return ol - l;
    }
    ll operator () () {
        ll f = 0;
        while (bfs()) f += dfs(s, LLONG_MAX);
        return f;
    }
} qwq;
struct Node {
    // bool used;
    ll d;
    struct Edge *e;
} g[N];
struct Edge {
    Node *u, *v;
    int w;
    Edge *e;
    Edge() {}
    Edge(Node *s, Node *t, cint x) : u(s), v(t), w(x), e(s->e) { s->e = this; }
} pool[M * 2], *curr = pool;
namespace SSSP {
    int n;
    void arc(Node *u, Node *v, int w) {
        new (curr++) Edge(u, v, w);
        new (curr++) Edge(v, u, w);
    }
    struct Pair {
        Node *u;
        ll d;
        Pair() {}
        Pair(Node *v, ll x) : u(v), d(x) {}
        bool operator < (const Pair &rh) const {
            return d > rh.d;
        }
    };
    std::priority_queue<Pair> q;
    void dijkstra() {
        rep (i, 2, n)
            g[i].d = LLONG_MAX;
        q.push(Pair(&g[1], g[1].d = 0));
        while (!q.empty()) {
            Node *u = q.top().u, *v;
            q.pop();
            int t;
            go (e, u->e) if ((v = e->v)->d > (t = u->d + e->w))
                q.push(Pair(v, v->d = t));
        }
    }
}
int main() {
    int n = SSSP::n = io, m = io;
    qwq.n = n * 2;
    qwq.s = &qwq[1];
    qwq.t = &qwq[qwq.n];
    rep (i, 1, m) {
        int u = io, v = io;
        SSSP::arc(&g[u], &g[v], io);
    }
    SSSP::dijkstra();
    for (Edge *e = pool; e < curr; ++e) if (e->u->d + e->w == e->v->d) {
        // ccc(e->u-g, e->v-g);
        qwq.arc(e->u - g + n, e->v - g, LLONG_MAX);
    }
    (int)io;
    qwq.arc(1, n + 1, LLONG_MAX);
    re (i, 2, n)
        qwq.arc(i, n + i, io);
    (int)io;
    qwq.arc(n, n + n, LLONG_MAX);

    io << qwq() daze;
}
