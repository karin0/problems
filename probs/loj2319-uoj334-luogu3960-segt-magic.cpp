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

const int N = 300003;
struct SegT {
    SegT *lc, *rc;
    ll x;  // ***
    int asz; // count removed items  
} pool[N * 4 * 20], *curr = pool;
ll rval;
int rpos;
void remove(SegT *&o, const int k, const int l, const int r) {
    if (!o)
        o = new (curr++) SegT;
    ++o->asz;
    if (l == r)
        return (void)(rpos = l, rval = o->x);
    int mid = (l + r) >> 1, lsz = mid - l + 1 - (o->lc ? o->lc->asz : 0);
    if (lsz >= k)
        remove(o->lc, k, l, mid);
    else
        remove(o->rc, k - lsz, mid + 1, r);
}
void insert(SegT *&o, const int i, const ll v, const int l, const int r) {
    if (!o)
        o = new (curr++) SegT;
    if (l == r)
        return (void)(o->x = v);
    int mid = (l + r) >> 1;
    if (i <= mid)
        insert(o->lc, i, v, l, mid);
    else
        insert(o->rc, i, v, mid + 1, r);
}
SegT *segt[N];
int n, m, len[N], l0, li;
ll query(const int x, const int y) {
    static ll res;
    if (y == m) {
        remove(segt[0], x, 1, l0);
        res = rpos <= n ? (ll)rpos * m : rval;
        insert(segt[0], ++len[0], res, 1, l0);
    } else {
        remove(segt[x], y, 1, li);
        res = rpos < m ? rpos + (ll)(x - 1) * m : rval;
        remove(segt[0], x, 1, l0);
        insert(segt[x], ++len[x], rpos <= n ? (ll)rpos * m : rval, 1, li);
        insert(segt[0], ++len[0], res, 1, l0);
    }
    return res;
}
int main() {
    static int i, q;
    n = io;
    m = io;
    q = io;
    len[0] = n;
    rep (i, 1, n)
        len[i] = m - 1;
    l0 = n + q;
    li = m - 1 + q;
    while (q--) {
        i = io;
        io.print(query(i, io));
    }

    return 0;
}

