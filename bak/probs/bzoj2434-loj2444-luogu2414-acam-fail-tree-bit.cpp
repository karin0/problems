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
    #define ccc(x)
    #define ccf(x)
    #define cccc(...)
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,const char end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;
typedef long long ll;

const int N = 100003, sig = 26;
int c[N], tim;
void inc(int i) {
    for (; i <= tim; i += i & -i)
        ++c[i];
}
void dec(int i) {
    for (; i <= tim; i += i & -i)
        --c[i];
}
int qry(int l, int r) {
    static int res;
    for (res = 0; r; r -= r & -r)
        res += c[r];
    for (--l; l; l -= l & -l)
        res -= c[l];
    return res;
}
struct Node {
    Node *ch[sig], *fa, *fail;
    struct Edge *e;
    bool w;
    std::vector<std::pair<Node *, int *> > qs;
    int dfn, siz;
    Node() {}
    Node(Node *_f) : fa(_f) {}
} *rt, *wd[N];
int wcnt;
struct Edge {
    Node *v;
    Edge *e;
    Edge() {}
    Edge(Node *_v, Edge *_e) : v(_v), e(_e) {}
};
void arc(Node *u, Node *v) {
    static Edge pool[N], *curr = pool;
    u->e = new (curr++) Edge(v, u->e);
}
int query(Node *u) {
    return qry(u->dfn, u->dfn + u->siz - 1);
}
char s[N];
static const char *p;
void init() {
    static Node pool[N], *curr = pool, *u;
    u = rt = new Node;
    for (p = s; *p; ++p) {
        if (*p == 'B')
            u = u->fa;
        else if (*p == 'P')
            u->w = true, wd[++wcnt] = u;
        else {
            Node *&v = u->ch[*p - 'a'];
            if (!v)
                v = new (curr++) Node(u);
            u = v;
        }
    }
}
void exec() {
    static Node *u; // *fa;  // this does not handle BBBBBBB
    static std::vector<std::pair<Node *, int *> >::iterator it, ed;
    u = rt;
    for (p = s; *p; ++p) {
        if (*p == 'B')
            dec(u->dfn), u = u->fa;
        else if (*p == 'P') {
            ed = u->qs.end();
            for (it = u->qs.begin(); it != ed; ++it)
                *it->second = query(it->first);
        } else {
            u = u->ch[*p - 'a'];
            inc(u->dfn);
        }
    }
}
void build() {
    static std::queue<Node *> q;
    static int i;
    static Node *u;
    rt->fail = rt;
    re (i, 0, sig) {
        Node *&v = rt->ch[i];
        if (v)
            arc(v->fail = rt, v), q.push(v);
        else
            v = rt;
    }
    while (!q.empty()) {
        u = q.front();
        q.pop();
        re (i, 0, sig) {
            Node *&v = u->ch[i];
            if (!v) {
                v = u->fail->ch[i];
                continue;
            }
            arc(v->fail = u->fail->ch[i], v);
            q.push(v);
        }
    }
}
void dfs(Node *u) {
    u->dfn = ++tim;
    u->siz = 1;
    for (Edge *e = u->e; e; e = e->e) {
        dfs(e->v);
        u->siz += e->v->siz;
    }
}
int main() {
    static int m, i, x, ans[N];
    io.gs(s);
    init();
    build();
    dfs(rt);
    m = io;
    rep (i, 1, m) {
        x = io;
        wd[(int)io]->qs.push_back(std::make_pair(wd[x], &ans[i]));
    }
    exec();
    rep (i, 1, m)
        io.print(ans[i]);

    return 0;
}

