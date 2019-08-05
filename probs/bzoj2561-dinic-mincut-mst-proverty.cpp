#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);/*p=b;*/}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;/*return s==t?EOF:*s++;*/}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,const char end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;
typedef long long ll;

const int N = 20003, M = 200003, inf = 0x7fffffff;
namespace g {
    int n;
    struct Node {
        struct Edge *e, *c;
        int d;
    } g[N], *s, *t;
    struct Edge {
        Node *v;
        Edge *e, *r;
        int c;
        Edge() {}
        Edge(Node *_v, Edge *_e, int _c) : v(_v), e(_e), c(_c) {}
    } pool[M * 2], *curr = pool;
    void arc(Node *u, Node *v, int c) {  // undirected edge 
        u->e = new (curr++) Edge(v, u->e, c);
        v->e = new (curr++) Edge(u, v->e, c);
        (u->e->r = v->e)->r = u->e;
    }
    bool bfs() {
        static Node *u, *v;
        static Edge *e;
        std::queue<Node *> q;
        rep (u, g + 1, g + n)
            u->d = 0, u->c = u->e;
        s->d = 1;
        q.push(s);
        while (!q.empty()) {
            u = q.front();
            q.pop();
            for (e = u->e; e; e = e->e) if (e->c && (v = e->v)->d == 0) {
                v->d = u->d + 1;  // do this sooner
                if (v == t)
                    return true;
                q.push(v);
            }
        }
        return false;
    }
    int dfs(Node *u, int l) {
        if (u == t || l == 0)
            return l;
        int f, res = 0; // init res
        for (Edge *&e = u->c; e; e = e->e) if (e->c && e->v->d == u->d + 1 && (f = dfs(e->v, std::min(l, e->c))) > 0) {
            e->c -= f;
            e->r->c += f;
            l -= f;
            res += f;
            if (l == 0)
                return res;
        }
        return res;
    }
    int res;
    void dinic() {
        while (bfs())
            res += dfs(s, inf);
    }
    void reset() {
        static Node *u;
        curr = pool;
        rep (u, g + 1, g + n)
            u->e = NULL;
    }
}
void arc(int u, int v) {
    g::arc(&g::g[u], &g::g[v], 1);
    // g::arc(&g::g[v], &g::g[u], 1);
}
int main() {
    static struct E {
        int u, v, w;
    } qwq[M];
    static int n, m, i, w;
    n = io;
    m = io;
    rep (i, 1, m) {
        E &e = qwq[i];
        e.u = io;
        e.v = io;
        e.w = io;
    }
    g::n = n;
    g::s = &g::g[(int)io];
    g::t = &g::g[(int)io];
    w = io;
    rep (i, 1, m) {
        const E &e = qwq[i];
        if (e.w < w)
            arc(e.u, e.v);
    }
    g::dinic();
    g::reset();
    rep (i, 1, m) {
        const E &e = qwq[i];
        if (e.w > w)
            arc(e.u, e.v);
    }
    g::dinic();
    io.print(g::res);

    return 0;
}
