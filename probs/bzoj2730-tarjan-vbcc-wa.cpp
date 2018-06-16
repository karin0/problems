#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define cccc(x) std::cerr << #x " = " << x << std::endl
    #define ccccc(x) std::cerr << x << std::endl
#else
    #define ccc(x) 0
    #define cccc(x) 0
    #define ccccc(x) 0
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);/*p=b;*/}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;/*return s==t?EOF:*s++;*/}void gs(char*st){static char c;for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static char c;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char c){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=c;}template<class T>void print(T x,const char end='\n'){static char c[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=c;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=c)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;

typedef long long ll;
const int N = 503, M = 502;
struct Node {
    int dfn, low;
    bool cut;
    struct Edge *e;
} g[N];
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *_u, Node *_v) : v(_v), e(_u->e) {
        _u->e = this;
    }
} pool[N * 2], *curr = pool;
void arc(Node *u, Node *v) {
    while (u == v);
    new Edge(u, v);
    new Edge(v, u);
}
int tim;
void tarjan(Node *u, Node *f) {
    u->low = u->dfn = ++tim;
    Node *v;
    int ch = 0;
    for (Edge *e = u->e; e; e = e->e) {
        v = e->v;
        if (v->dfn)
            u->low = std::min(u->low, v->dfn);
        else {
            ++ch;
            tarjan(v, u);
            u->low = std::min(u->low, v->low);
            if (f && u->dfn <= v->low) // ***
                u->cut = true;
        }
    }
    if (!f && ch > 1)
        u->cut = true;
}

int main() {
    static int kc, n, m, i, ans;
    static ll ans2 = 1;
    for (kc = 1; (m = io); ++kc) {
        // reset();
        n = 0;
        ans = 0;
        ans2 = 1;
        tim = 0;
        curr = pool;
        rep (i, 1, m) {
            static int u, v;
            n = std::max(n, std::max(u = io, v = io));
            arc(&g[u], &g[v]);
        }
        //rep (i, 1, n)
        //    if (!g[i].dfn)
        tim = 0;
        tarjan(&g[1], NULL);
        rep (i, 1, n)
            while (g[i].dfn == 0);
        rep (i, 1, n)
            g[i].dfn = 0;
        rep (i, 1, n) {
            static int siz;
            static Node *u, *v; //*cuts[N];
            if (g[i].cut || g[i].dfn)
                continue;
            // cnt = 0;
            std::queue<Node *> q;
            siz = 0;
            q.push(&g[i]);
            g[i].dfn = 1;
            std::set<Node *> s;
            while (!q.empty()) {
                u = q.front();
                q.pop();
                ++siz;
                for (Edge *e = u->e; e; e = e->e) {
                    v = e->v;
                    if (v->cut) {
                        // cccc(v-g);
                        s.insert(v);
                        // cuts[++cnt] = v;
                        // cuts[++cnt] = ;
                    } else if (!v->dfn)
                        v->dfn = 1, q.push(v);
                }
            }
            /*
            rep (j, 1, cnt)
                cuts[j]->dfn = 0;*/
            // printf("WE FOUND cnt = %d, siz = %d\n", cnt, siz);
            /* if (cnt == 0) {
                ans += 2;
                ans2 *= (ll)siz * (siz - 1) >> 1; */
            if (s.size() == 1) {
                ans += 1;
                ans2 *= siz;
            } /* else if (s.size() == 0) {
                ans += 2;
                ans2 *= (ll)siz * (siz - 1) / 2;
            } */
        }
        if (!ans)
           ans = 2, ans2 = (ll)n * (n - 1) / 2;
        // printf("Case %d: %d %lld\n", kc, ans, ans2);
        io.ps("Case ", 0);
        io.print(kc, ':');
        io.pc(' ');
        io.print(ans, ' ');
        io.print(ans2); 
        rep (i, 1, n) {
            g[i].dfn = g[i].low = 0;
            g[i].cut = false;
            g[i].e = NULL;
        }
    }

    return 0;
}
