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
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}char*gs(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return x+1;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p;*this>>p;if(c=='.'){int y=0,k=0;for(c=gc();isdigit(c);c=gc())y=y*10+(c-'0'),++k;x=(double)y/p_[k-1];if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 300004;
struct Node {
#define lc ch[0]
#define rc ch[1]
    Node *ch[2], *fa, *pfa;
    int x, sum;
    bool rev;
    static void link(Node *o, Node *p, cint r) {
        if (o) o->fa = p;
        if (p) p->ch[r] = o;
    }
    int rel() const { return fa && this == fa->rc; }
    void maintain() { sum = x ^ (lc ? lc->sum : 0) ^ (rc ? rc->sum : 0); }
    void push_down() {
        if (rev) {
            std::swap(lc, rc);
            if (lc) lc->rev ^= 1;
            if (rc) rc->rev ^= 1;
            rev = false;
        }
    }
    void rotate() {
        Node *f = fa;
        if (f->fa) f->fa->push_down();
        f->push_down(); push_down();
        int r = rel();
        link(this, f->fa, f->rel());
        link(ch[r ^ 1], f, r);
        link(f, this, r ^ 1);
        f->maintain();
        maintain();
        std::swap(pfa, f->pfa); // ****
    }
    void splay() {
        while (fa) {
            if (fa->fa == NULL) return rotate();
            else {
                fa->fa->push_down(); fa->push_down(); push_down();
                if (fa->rel() == rel()) fa->rotate();
                else rotate();
                rotate();
            }
        }
    }
    void expose() {
        splay();
        push_down();
        if (rc) {
            rc->fa = NULL;
            rc->pfa = this;
            rc = NULL;
            maintain();
        }
    }
    bool splice() {
        splay();
        if (!pfa) return false;
        pfa->expose();
        pfa->rc = this;
        fa = pfa;
        pfa = NULL;
        fa->maintain();
        return true;
    }
    void access() {
        for (expose(); splice(); );
        splay();
    }
    void evert() {
        access();
        rev ^= 1;
    }
    Node *find() {
        access();
        Node *o = this;
        while (o->push_down(), o->lc) o = o->lc;
        return o;
    }
    void modify(cint v) {
        splay();
        x = v;
        maintain();
    }
} g[N];
bool connected(Node *u, Node *v) {
    return u->find() == v->find();
}
void link(Node *u, Node *v) {
    v->evert();
    v->pfa = u;
}
int query(Node *u, Node *v) {
    u->evert();
    v->access();
    return v->sum;
}
void try_cut(Node *u, Node *v) {
    if (!connected(u, v))
        return;
    u->evert();
    v->access();
    v->push_down();
    //if (v->lc != u)
    //    return;
    u->fa = NULL;
    v->lc = NULL;
    v->maintain();
}

int n, m;
int main() {
    io >> n >> m;
    rep (i, 1, n)
        g[i].x = g[i].sum = io;
    while (m--) {
        cchar op = io;
        Node *u = &g[(int)io];
        if (op == '3')
            u->modify(io);
        else {
            Node *v = &g[(int)io];
            switch (op) {
                case '0': io << query(u, v) daze; break;
                case '1': if (!connected(u, v)) link(u, v); break;
                default : try_cut(u, v);
            }
        }
    }
    return 0;
}
