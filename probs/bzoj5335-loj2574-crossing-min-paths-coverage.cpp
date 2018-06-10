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

const int N = 504, M = 54, inf = 0x7fffffff;
namespace g {
    int n;
    struct Node {
        struct Edge *e, *c;
        int d;
    } g[N * 2], *s, *t;
    struct Edge {
        Node *v;
        Edge *e, *r;
        int c;
        Edge() {}
        Edge(Node *_v, Edge *_e, int _c) : v(_v), e(_e), c(_c) {}
    } pool[N * N * 2], *curr = pool;
    void arc(Node *u, Node *v, int c) {
        // cccc("Arcing %ld to %ld\n",u-g,v-g);
        u->e = new (curr++) Edge(v, u->e, c);
        v->e = new (curr++) Edge(u, v->e, 0);
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
            for (e = u->e; e; e = e->e) if (e->c > 0 && (v = e->v)->d == 0) {
                v->d = u->d + 1;
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
        int f, res = 0;
        for (Edge *&e = u->c; e; e = e->e) if (e->c > 0 && e->v->d == u->d + 1 && (f = dfs(e->v, std::min(l, e->c))) > 0) {
            e->c -= f;
            e->r->c += f;
            l -= f;
            res += f;
            if (l == 0)
                return res;
        }
        return res;
    }
    int dinic() {
        static int res;
        for (res = 0; bfs(); res += dfs(s, inf));
        return res;
    }
    void reset() {
        static Node *u;
        curr = pool;
        rep (u, g + 1, g + n)
            u->e = NULL;
    }
}
int n, m, w[N];
void arc(int u, int v) {
    g::arc(&g::g[u], &g::g[n + v], 1);
}
std::bitset<N> d[N];
bool check(const int x) {
    static int i, j, cnt;
    // ccc(x);
    g::reset();
    cnt = 0;
    rep (i, 1, n) if (w[i] < x) {
        ++cnt;
        g::arc(g::s, &g::g[i], 1), g::arc(&g::g[n + i], g::t, 1);
        rep (j, 1, n)
            if (i != j && w[j] < x && d[i].test(j))
                arc(i, j); // ccc(i), ccf(j);
    }
    return cnt - g::dinic() <= m;
}
int main() {
    static int i, j, x, rha[N], *end, l = 1, r;
    m = (int)io + 1;
    n = io;
    g::n = n * 2 + 2;
    g::t = g::g + g::n;
    g::s = g::t - 1;
    rep (i, 1, n) {
        rha[i] = w[i] = io;
        x = io;
        d[i].set(i);
        while (x--)
            d[i].set(io);
    }
    rep (i, 1, n)
        rep (j, 1, n)
            if (d[j].test(i))
                d[j] |= d[i];
    std::sort(rha + 1, rha + n + 1);
    end = std::unique(rha + 1, rha + n + 1);
    r = end - rha + 1;
    rep (i, 1, n)
        w[i] = std::lower_bound(rha + 1, end, w[i]) - rha;
    while (r - l > 1) {
        x = (l + r) >> 1;
        (check(x) ? l : r) = x;
    }
    // ccc(l); ccf(r);
    if (l >= end - rha)
        io.ps("AK");
    else
        io.print(rha[l]);

    return 0;
}
