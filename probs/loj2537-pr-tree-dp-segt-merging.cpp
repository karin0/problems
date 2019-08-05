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
const int N = 300005, mo = 998244353, inv1w = 796898467;

int mck(const int x) {
    return x >= mo ? x - mo : x;
}
int n, m, ans, rhash[N];
struct SegT {
    SegT *lc, *rc;
    int sum, tag;
    SegT() : sum(1), tag(1) {}
    void *operator new (size_t) {
        static SegT pool[N * 20], *curr = pool;
        return curr++;
    }
    void cover(ll v) {
        sum = sum * v % mo;
        tag = tag * v % mo;
    }
    void push_down() {
        if (tag != 1) {
            if (lc)
                lc->cover(tag);
            if (rc)
                rc->cover(tag);
            tag = 1;
        }
    }
    void push_down2() {
        if (tag != 1) {
            lc->cover(tag);
            rc->cover(tag);
            tag = 1;
        }
    }
    void maintain() {
        sum = 0;
        if (lc)
            sum += lc->sum;
        if (rc)
            sum += rc->sum;
        sum = mck(sum);
    }
    void calc(const int l = 1, const int r = m) {
        if (l == r) {
            ans = (ans + (ll)l * rhash[l] % mo * sum % mo * sum % mo) % mo;
            return;
        }
        push_down2();
        int mid = (l + r) >> 1;
        lc->calc(l, mid);
        rc->calc(mid + 1, r);
    }
};
void uins(SegT *&o, const int i, const int l = 1, const int r = m) {
    if (!o) {
        o = new SegT;
        o->sum = o->tag = 1;
    }
    if (l == r) 
        return;
    int mid = (l + r) >> 1;
    if (i <= mid)
        uins(o->lc, i, l, mid);
    else
        uins(o->rc, i, mid + 1, r);
    // maintain();
}
int pr;
int gsum(const SegT *o) {
    return o ? o->sum : 0;
}
SegT *merge(SegT *p, SegT *q, const ll x, const ll y) {
    if (!p && !q)
        return NULL;
    if (!q)
        return p->cover(y), p;
    if (!p)
        return q->cover(x), q;
    p->push_down();
    q->push_down();
    ll pls = gsum(p->lc), qls = gsum(q->lc), prs = gsum(p->rc), qrs = gsum(q->rc);
    p->lc = merge(p->lc, q->lc, mck(x + prs * (mo + 1 - pr) % mo), mck(y + qrs * (mo + 1 - pr) % mo));
    p->rc = merge(p->rc, q->rc, mck(x + pls * pr % mo), mck(y + qls * pr % mo));
    p->maintain();
    return p;
}
struct Node {
    Node *ch[2];
    int w;
} g[N], *lea[N];
SegT *dfs(Node *u) {
    if (!u->ch[0]) {
        SegT *o = NULL;
        uins(o, u->w);
        return o;
    }
    if (!u->ch[1])
        return dfs(u->ch[0]);
    SegT *l = dfs(u->ch[0]), *r = dfs(u->ch[1]); // we have to do this earlier for no reason
    pr = u->w;
    return merge(l, r, 0, 0);
}
int main() {
    static int i, x;
    n = io;
    i = io;
    rep (i, 2, n) {
        x = io;
        g[x].ch[g[x].ch[0] ? 1 : 0] = &g[i];
    }
    rep (i, 1, n) {
        g[i].w = io;
        if (g[i].ch[0])
            g[i].w = (ll)g[i].w * inv1w % mo;
        else
            lea[++m] = &g[i];
    }
    std::sort(lea + 1, lea + m + 1, [](const Node *lh, const Node *rh) { return lh->w < rh->w; } );
    rep (i, 1, m) {
        rhash[i] = lea[i]->w % mo;
        lea[i]->w = i;
    }
    ans = 0;
    dfs(&g[1])->calc(1, m);
    io.print(ans);

    return 0;
}
