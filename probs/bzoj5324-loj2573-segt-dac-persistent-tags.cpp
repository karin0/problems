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
int n, p;
int mul(const int x, const int y) {
    return (ll)x * y % p;
}
void cmul(int &x, const int y) {
    x = mul(x, y);
}
struct SegT {
    SegT *lc, *rc;
    int x;
    SegT() {}
    SegT(SegT *_l, SegT *_r) : lc(_l), rc(_r), x(1) {}
    void cover(int v) {
        cmul(x, v);
    }
    void update(const int ql, const int qr, const int v, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
            cover(v);
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->update(ql, qr, v, l, mid);
        if (qr > mid)
            rc->update(ql, qr, v, mid + 1, r);
    }
    int query(const int qi, const int l = 1, const int r = n) {
        if (l == r)
            return x;
        int mid = (l + r) >> 1;
        if (qi <= mid)
            return mul(x, lc->query(qi, l, mid));
        return mul(x, rc->query(qi, mid + 1, r));
    }
} *segt, pool[N * 2], *curr;
SegT *build(const int l, const int r) {
    if (l == r)
        return new (curr++) SegT(NULL, NULL);
    int mid = (l + r) >> 1;
    return new (curr++) SegT(build(l, mid), build(mid + 1, r));
}
int main() {
    static struct Range {
        int l, r, x;
    } qwq[N];
    static int ks, i, op, x;
    ks = io;
    while (ks--) {
        n = io;
        p = io;
        rep (i, 1, n) {
            op = io;
            x = io;
            Range &q = qwq[i];
            if (op == 1) {
                q.l = i;
                q.r = n;
                q.x = x;
            } else {
                qwq[x].r = i - 1;
                q.x = -1;
            }
        }
        curr = pool;
        segt = build(1, n);
        rep (i, 1, n) {
            const Range &q = qwq[i];
            if (q.x >= 0)
                segt->update(q.l, q.r, q.x);
        }
        rep (i, 1, n)
            io.print(segt->query(i));
    }

    return 0;
}
