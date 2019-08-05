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

const int N = 80007;
struct Node *rt;
struct Node {
    Node *ch[2], *fa;
    int x, siz;
    Node() {}
    Node(const int _x, Node *_f) : fa(_f), x(_x), siz(1) {}
    static void link(Node *o, Node *f, const int r) {
        if (o)
            o->fa = f;
        if (f)
            f->ch[r] = o;
    }
    void maintain() {
        siz = 1 + (ch[0] ? ch[0]->siz : 0) + (ch[1] ? ch[1]->siz : 0);
    }
    int rel() {
        return fa && this == fa->ch[1];
    }
    void rotate() {
        static Node *f;
        static int r;
        f = fa;
        r = rel();
        link(this, f->fa, f->rel());
        link(ch[r ^ 1], f, r);
        link(f, this, r ^ 1);
        f->maintain();
        maintain();
        if (fa == NULL)
            rt = this;
    }
    void splay(Node *des = NULL) {
        while (fa != des) {
            if (fa->fa == des)
                return rotate();
            else if (rel() == fa->rel())
                fa->rotate(), rotate();
            else
                rotate(), rotate();
        }
    } // inc
    int rk() {
        return ch[0] ? ch[0]->siz : 0;
    }
    Node *succ() {
        Node *o = ch[1];
        for (; o->ch[0]; o = o->ch[0]);
        return o;
    }
    Node *prev() {
        Node *o = ch[0];
        for (; o->ch[1]; o = o->ch[1]);
        return o;
    }
    void cut() {
        splay();
        if (ch[1]) {
            Node *o = succ();
            o->splay(this);
            link(ch[0], o, 0);
            rt = o;
        } else
            rt = ch[0];
        rt->fa = NULL;
        rt->maintain();
        ch[0] = ch[1] = fa = NULL;
    }
    void *operator new (size_t) {
        static Node pool[N], *curr = pool;
        return curr++;
    }
} *mp[N];
void link(Node *o, Node *f, const int r) {
    if (o)
        o->fa = f;
    if (f)
        f->ch[r] = o;
}
int n, seq[N];
Node *build(const int l, const int r, Node *f) {
    if (l > r)
        return NULL;
    int mid = (l + r) >> 1;
    Node *o = new Node(seq[mid], f);
    mp[seq[mid]] = o;
    if (l != r) {
        o->ch[0] = build(l, mid - 1, o);
        o->ch[1] = build(mid + 1, r, o);
        o->maintain();
    }
    return o;
}
Node *select(int x) {
    Node *o = rt;
    while (true) {
        int ork = o->rk();
        if (ork < x)
            o = o->ch[1], x -= ork + 1;
        else if (ork > x)
            o = o->ch[0];
        else
            return o->splay(), o;
    }
}
Node *select2(int x) {
    Node *o = rt;
    for (; o->ch[x]; o = o->ch[x]);
    return o->splay(), o;
}
void move_to(const int x, const int r) {
    mp[x]->cut();
    link(select2(r), mp[x], r ^ 1);
    rt = mp[x];
    rt->maintain();
}
int query_rk(const int x) {
    mp[x]->splay();
    return mp[x]->rk();
}
int query_at(const int x) {
    return select(x - 1)->x;
}
void insert(const int x, const int d) {
    if (!d)
        return;
    mp[x]->splay();
    Node *p = d == 1 ? mp[x]->succ() : mp[x]->prev();
    int y = p->x;
    mp[x]->x = y;
    p->x = x;
    mp[y] = mp[x];
    mp[x] = p;
}

int main() {
    static int m, i, x;
    static char op[20];
    n = io;
    m = io;
    rep (i, 1, n)
        seq[i] = io;
    rt = build(1, n, NULL);
    while (m--) {
        io.gs(op);
        x = io;
        // printf("Doing %s %d\n", op, x);
        switch (op[0]) {
            case 'T': move_to(x, 0); break;
            case 'B': move_to(x, 1); break;
            case 'I': insert(x, io); break;
            case 'A': io.print(query_rk(x)); break;
            default : io.print(query_at(x));
        }
    }

    return 0;
}
