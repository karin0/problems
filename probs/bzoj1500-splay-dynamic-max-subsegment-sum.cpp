#include <bits/stdc++.h>
#define rep(i_,s_,t_) for((i_)=(s_);(i_)<=(t_);++(i_))
#define re(i_,s_,t_) for((i_)=(s_);(i_)<(t_);++(i_))
#define per(i_,s_,t_) for((i_)=(s_);(i_)>=(t_);--(i_))
#define pe(i_,s_,t_) for((i_)=(s_);(i_)>(t_);--(i_))
#define koishi(e_,u_) for(Edge *e_=(u)_->e;e_;e_=e_->e)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
struct IO{static cint L=1000000;char a[L],b[L],*s,*t,*z,c;IO():z(b){}~IO(){fl();}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}template<class T>operator T(){static T x;static bool f;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((f=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return f?-x:x;}void gs(char*q){for(c=gc();!isgraph(c);c=gc());*q++=c;for(c=gc();isgraph(c);c=gc())*q++=c;*q++=0;}char gg(){for(c=gc();!isgraph(c);c=gc());return c;}void pc(cchar q){if(z==b+L)fwrite(z=b,1,L,stdout);*z++=q;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>void operator()(T x,cchar e='\n'){static char r[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=r;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=r)pc(*--q);}if(e)pc(e);}void ps(cchar*q,cchar e='\n'){while(*q)pc(*q++);if(e)pc(e);}void pd(cint x){pc('0'+x);pc('\n');}}io;

const int N = 500007;
/*template <class T, int S>
struct Pool {
    T pool[S], *curr, *rpool[S], **rcurr;
    Pool() : curr(pool), rcurr(rpool) {}
    T *operator () () {
        return rcurr > rpool ? --rcurr : curr++;
    }
    void collect(T *p) {
        rcurr++ = p;
    }
} pool; */
using std::max;
int max(const int a, const int b, const int c) { return max(max(a, b), c); }
struct Node *rt;
int gsum(const Node *const o);
int gsiz(const Node *const o);
int gmxs(const Node *const o);
int glmxs(const Node *const o);
int grmxs(const Node *const o);
#define lc ch[0]
#define rc ch[1]
// int pcnt;
struct Node {
    Node *ch[2], *fa;
    int x, siz, sum, mxs, lmxs, rmxs;
    bool tflip, tcov;
    Node() {}
    Node(const int x_, Node *const f_) : fa(f_), siz(1) {
        x = sum = mxs = x_;
        lmxs = rmxs = std::max(x, 0);
        tflip = tcov = false;
        lc = rc = NULL; // new 出来的
    }
    ~Node() {
        if (lc) delete lc;
        if (rc) delete rc;
    }
    bool rel() const { return fa && this == fa->ch[1]; }
    static void link(Node *o, Node *f, const bool r) {
        if (o) o->fa = f;
        if (f) f->ch[r] = o;
    }
    void rotate() {
        Node *f = fa;
        bool r = rel();
        link(this, f->fa, f->rel());
        link(ch[r ^ 1], f, r);
        link(f, this, !r);
        f->maintain();
        maintain();
        if (!fa) rt = this;
    }
    void splay(Node *p = NULL) {
        while (fa != p) {
            if (fa->fa == p) return rotate();
            else if (fa->rel() == rel()) fa->rotate(), rotate();
            else rotate(), rotate();
        }
    }
    void maintain() {
        siz = 1 + gsiz(lc) + gsiz(rc);
        sum = x + gsum(lc) + gsum(rc);
        lmxs = max(glmxs(lc), gsum(lc) + x + glmxs(rc));
        rmxs = max(grmxs(rc), gsum(rc) + x + grmxs(lc));
        mxs = max(gmxs(lc), gmxs(rc), x + grmxs(lc) + glmxs(rc));
    }
    void flip() {
        std::swap(lc, rc);
        std::swap(lmxs, rmxs); // *************
        tflip = !tflip;
    }
    void cover(const int v) {
        x = v;
        sum = v * siz;
        lmxs = rmxs = max(sum, 0);
        mxs = max(sum, v);
        tcov = true;
    }
    void push_down() {
        if (tcov) {
            tcov = tflip = false;
            if (lc) lc->cover(x);
            if (rc) rc->cover(x);
        } else if (tflip) {
            tflip = false;
            if (lc) lc->flip();
            if (rc) rc->flip();
        }
    }
    int rank() const { return gsiz(lc); }
    /* void print() {
        if (lc) lc->print();
        ccc(++pcnt, x, siz, sum, mxs, lmxs, rmxs);
        if (rc) rc->print();
    } */
};
// void print() {
    // pcnt = 0;
    // rt->print();
// }
int gsum(const Node *const o) { return o ? o->sum : 0; }
int gsiz(const Node *const o) { return o ? o->siz : 0; }
int gmxs(const Node *const o) { return o ? o->mxs : -114514; }  // *****
int glmxs(const Node *const o) { return o ? o->lmxs : 0; }
int grmxs(const Node *const o) { return o ? o->rmxs : 0; }
Node *select(int k) {
    --k;
    Node *o = rt;
    while (true) {
        int ork = o->rank();
        o->push_down(); // ***
        if (ork < k)
            k -= ork + 1, o = o->rc;
        else if (ork > k)
            o = o->lc;
        else
            return o->splay(), o;
    }
}
struct RangeSelector {
    Node *o, *p;
    Node *& select_(const int l, const int r) {
        o = p = NULL;
        if (r == rt->siz) {
            if (l == 1) return rt;
            return (p = select(l - 1))->rc;
        }
        p = select(r + 1);
        if (l == 1) return p->lc;
        o = select(l - 1);
        p->splay(o);
        return p->lc;
    }
    Node *& operator () (const int l, const int r) {
        Node *&rr = select_(l, r);
        rr->push_down();
        return rr;
    }
    void maintain() {
        if (p) p->maintain();
        if (o) o->maintain();
    }
} range;
int a[N];
Node *build(const int l, const int r, Node *f) {
    if (l > r)
        return NULL;
    int mid = (l + r) >> 1;
    Node *o = new Node(a[mid], f);
    if (l != r) {
        o->ch[0] = build(l, mid - 1, o);
        o->ch[1] = build(mid + 1, r, o);
        o->maintain();
    }
    return o;
}
void insert(const int i, const int n) {
    /* if (!rt)
        return (void)(rt = build(1, n, NULL)); */
    Node *o;
    if (i == 0) {
        o = range(1, 1);
        o->lc = build(1, n, o);
    } else {
        o = range(i, i);
        o->rc = build(1, n, o);
    }
    o->maintain();
    range.maintain();
}
void remove(const int l, const int r) {
    Node *&o = range(l, r);
    // ccc(o->sum, o->x, rt->siz);
    delete o;
    o = NULL;
    range.maintain();
    // ccc(rt->siz);
}
void cover(const int l, const int r, const int v) {
    Node *o = range(l, r);
    o->cover(v); o->push_down();
    range.maintain();
}
void flip(const int l, const int r) {
    Node *o = range(l, r);
    o->flip(); o->push_down();
    range.maintain();
}
int sum(const int l, const int r) {
    return range(l, r)->sum;
}

int main() {
    static int n, m, p, t, i, j;
    static char opt[14];
    n = io;
    m = io;
    rep (i, 1, n)
        a[i] = io;
    rt = build(1, n, NULL);
    rep (j, 1, m) {
        io.gs(opt);
        if (opt[2] == 'X') {
            if (rt->mxs < 0) ccc(j, rt->siz, rt->sum, rt->x, rt->lmxs, rt->rmxs, rt->mxs, rt->lc->mxs, rt->rc->mxs);
            io(rt->mxs);
        } else {
            p = io; t = io;
            // ccc(opt, p, t, rt->siz);
            switch (opt[0]) {
                case 'I': if (!t) break;
                          rep (i, 1, t)
                              a[i] = io;
                          insert(p, t); break;
                case 'D': if (t) remove(p, p + t - 1); break;
                case 'M': if (t) cover(p, p + t - 1, io); break;
                case 'R': if (t) flip(p, p + t - 1); break;
                default:  t ? io(sum(p, p + t - 1)) : (io.pc('0'), io.pc('\n'));
            }
        }
        // io.fl();
    }

    return 0;
}
