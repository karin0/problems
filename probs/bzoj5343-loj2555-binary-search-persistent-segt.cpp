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

const int N = 100003;
int mx;
struct SegT *nil;
struct SegT {
    SegT *lc, *rc;
    ll sp, sc;
    SegT() {}
    SegT(SegT *_l, SegT *_r) : lc(_l), rc(_r), sp(lc->sp + rc->sp), sc(lc->sc + rc->sc) {}
    SegT(int p, ll c) : lc(nil), rc(nil), sp(p * c), sc(c) {}
    SegT *insert(const int i, const int p, const int c, const int l = 1, const int r = mx) const {
        if (l == r)
            return new SegT(p, sc + c);  // ****
        int mid = (l + r) >> 1;
        if (i <= mid)
            return new SegT(lc->insert(i, p, c, l, mid), rc);
        else
            return new SegT(lc, rc->insert(i, p, c, mid + 1, r));
    }
    ll query(const ll cash, const int l = 1, const int r = mx) const {
        if (this == nil)
            return 0;
        if (sp <= cash)
            return sc;   // ****
        if (l == r)
            return cash / (sp / sc);
        int mid = (l + r) >> 1;
        if (lc->sp <= cash)
            return lc->sc + rc->query(cash - lc->sp, mid + 1, r);
        return lc->query(cash, l, mid);
    }
    void *operator new (size_t) {
        static SegT pool[N * 20], *curr = pool;
        return curr++;
    }
} *segt[N];
struct Item {
    int d, p, l;
    bool operator < (const Item &rh) const {
        return d > rh.d;
    }

} qwq[N];
int n, rha[N];
int query(ll cash, ll requ) {
    static int l, r, x;
    l = 1, r = n;
    while (l < r) {
        x = (l + r) >> 1;
        if (segt[x]->query(cash) >= requ)
            r = x;
        else
            l = x + 1;
    }
    /* if (segt[l]->query(cash) >= requ)
        r = l; */
    if (l > r || segt[r]->query(cash) < requ)
        return -1;
    return qwq[r].d;
}
int main() {
    segt[0] = nil = new SegT;
    nil->lc = nil->rc = nil;
    static int i, m, *ed;
    n = io;
    m = io;
    rep (i, 1, n) {
        Item &q = qwq[i];
        q.d = io;
        rha[i] = q.p = io;
        q.l = io;
    }
    std::sort(qwq + 1, qwq + n + 1);
    std::sort(rha + 1, rha + n + 1);
    ed = std::unique(rha + 1, rha + n + 1);
    mx = ed - 1 - rha;
    rep (i, 1, n)
        segt[i] = segt[i - 1]->insert(std::lower_bound(rha + 1, ed, qwq[i].p) - rha, qwq[i].p, qwq[i].l);
    rep (i, 1, m) {
        static ll g;
        g = io;
        io.print(query(g, io));
    }


    return 0;
}
