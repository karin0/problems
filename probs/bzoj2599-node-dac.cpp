#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#define pern(__e, __u) for(Edge *__e=__u->e; __e; __e=__e->e)
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
struct IO{static cint L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(cchar ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,cchar end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(cchar*st,cchar end='\n'){while(*st)pc(*st++);if(end)pc(end);}void pd(cint x){pc('0'+x);pc('\n');}}io;

const int N = 200002, K = 1000002, inf = 0x3f3f3f3f;
void chmin(int &x, const int v) {
    x = std::min(x, v);
}
void chmax(int &x, const int v) {
    x = std::max(x, v);
}
struct Node {
    bool done;
    int dep, sum, siz, ms;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    int w;
    Edge *e;
    Edge() {}
    Edge(Node *_u, Node *_v, const int _w) : v(_v), w(_w), e(_u->e) {
        _u->e = this;
    }
} pool[N * 2], *curr = pool;
int n, k, ans = inf, tim, f[K];
Node *seq[N];
void dfs0(Node *u, Node *fa) {
    seq[++tim] = u;
    u->siz = 1;
    u->ms = 0; // ***
    pern (e, u) if (!e->v->done && e->v != fa) {
        dfs0(e->v, u);
        u->siz += e->v->siz;
        chmax(u->ms, e->v->siz);
    }
}
void dfs1(Node *u, Node *fa) {
    seq[++tim] = u;
    if (f[k - u->sum] < inf)
        chmin(ans, u->dep + f[k - u->sum]);
    pern (e, u) if (!e->v->done && e->v != fa && (ll)u->sum + e->w <= k) {
        e->v->dep = u->dep + 1;
        e->v->sum = u->sum + e->w;
        dfs1(e->v, u);
    }
}
Node *center(Node *u) {
    static int i, t, rv;
    static Node *res;
    tim = 0;
    dfs0(u, NULL);
    res = u;
    rv = u->ms;
    rep (i, 2, tim) if ((t = std::max(seq[i]->ms, u->siz - seq[i]->siz)) < rv)
        rv = t, res = seq[i];
    return res;
}
void calc(Node *u) {
    static int i, ot;
    tim = 0;
    f[0] = 0;
    pern (e, u) if (!e->v->done && e->w <= k) {
        e->v->dep = 1;
        e->v->sum = e->w;
        ot = tim;
        dfs1(e->v, NULL);
        rep (i, ot + 1, tim)
            chmin(f[seq[i]->sum], seq[i]->dep);
    }
    rep (i, 1, tim)
        f[seq[i]->sum] = inf;
}
void solve(Node *u) {
    u = center(u);
    u->done = true;
    calc(u);
    pern(e, u) if (!e->v->done)
        solve(e->v);
}
int main() {
    static int i, u, v, w;
    n = io;
    k = io;
    std::fill(f + 1, f + k + 1, inf);
    re (i, 1, n) {
        u = io;
        v = io;
        w = io;
        new (curr++) Edge(&g[u], &g[v], w);
        new (curr++) Edge(&g[v], &g[u], w);
    }
    solve(&g[0]);
    io.print(ans < inf ? ans : -1);
    return 0;
}

