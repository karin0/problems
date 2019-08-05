#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define ccf(x) std::cerr << #x " = " << x << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);/*p=b;*/}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;/*return s==t?EOF:*s++;*/}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,const char end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;
typedef long long ll;

const int N = 500003, inf = 1 << 30;
int n;
struct SegT {
    SegT *lc, *rc;
    ll sum;
    int len, mx, smx, cmx, mn, smn, cmn, tadd; // tcmn, tcmx; // they can be replaced by mx and mn
    SegT() {}
    SegT(int x) : sum(x), len(1), mx(x), smx(-inf), cmx(1), mn(x), smn(inf), cmn(1), tadd(0) {}
    SegT(SegT *_lc, SegT *_rc, int _l) : lc(_lc), rc(_rc), len(_l), tadd(0) {
        maintain();
    }
    void maintain() {
        sum = lc->sum + rc->sum;
        if (lc->mx > rc->mx)
            mx = lc->mx, cmx = lc->cmx, smx = std::max(lc->smx, rc->mx);
        else if (lc->mx < rc->mx)
            mx = rc->mx, cmx = rc->cmx, smx = std::max(lc->mx, rc->smx);
        else
            mx = lc->mx, cmx = lc->cmx + rc->cmx, smx = std::max(lc->smx, rc->smx);
        if (lc->mn < rc->mn)
            mn = lc->mn, cmn = lc->cmn, smn = std::min(lc->smn, rc->mn);
        else if (lc->mn > rc->mn)
            mn = rc->mn, cmn = rc->cmn, smn = std::min(lc->mn, rc->smn);
        else
            mn = lc->mn, cmn = lc->cmn + rc->cmn, smn = std::min(lc->smn, rc->smn);
    }
    void push_down() {
        if (tadd != 0) {
            lc->cadd(tadd);
            rc->cadd(tadd);
            tadd = 0;
        }
        if (lc->mn < mn)
            lc->cmax(mn);
        if (rc->mn < mn)
            rc->cmax(mn);
        if (lc->mx > mx)
            lc->cmin(mx);
        if (rc->mx > mx)
            rc->cmin(mx);
    }
    void cadd(const int x) {
        sum += (ll)x * len;  // ***** ll
        mx += x, smx += x, mn += x, smn += x;
        tadd += x;
    }
    void cmin(const int x) { // assuming smx < x < mx
        sum += (ll)cmx * (x - mx);  // **** ll
        mx = x;
        mn = std::min(mn, x);
        if (x == mn)
            cmn = len, smn = inf;
        else // mn does not change
            smn = std::min(smn, x);
    }
    void cmax(const int x) { // assuming smn > x > mn
        sum += (ll)cmn * (x - mn);
        mn = x;
        mx = std::max(mx, x);
        if (x == mx)
            cmx = len, smx = -inf;
        else
            smx = std::max(smx, x);
    }
    void uadd(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr) {
            cadd(x);
            return;
        }
        push_down(); // *****
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->uadd(ql, qr, x, l, mid);
        if (qr > mid)
            rc->uadd(ql, qr, x, mid + 1, r);
        maintain();
    }
    void umin(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
        if (mx <= x)
            return;
        if (ql <= l && r <= qr && smx < x) {
            cmin(x);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->umin(ql, qr, x, l, mid);
        if (qr > mid)
            rc->umin(ql, qr, x, mid + 1, r);
        maintain();
    }
    void umax(const int ql, const int qr, const int x, const int l = 1, const int r = n) {
        if (mn >= x)
            return;
        if (ql <= l && r <= qr && smn > x) {
            cmax(x);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->umax(ql, qr, x, l, mid);
        if (qr > mid)
            rc->umax(ql, qr, x, mid + 1, r);
        maintain();
    }
    ll qsum(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return sum;
        push_down();
        int mid = (l + r) >> 1;
        ll res = 0;
        if (ql <= mid)
            res = lc->qsum(ql, qr, l, mid);
        if (qr > mid)
            return res + rc->qsum(ql, qr, mid + 1, r);
        return res;
    }
    int qmin(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return mn;
        push_down();
        int mid = (l + r) >> 1, res = inf;
        if (ql <= mid)
            res = std::min(res, lc->qmin(ql, qr, l, mid));
        if (qr > mid)
            return std::min(res, rc->qmin(ql, qr, mid + 1, r));
        return res;
    }
    int qmax(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return mx;
        push_down();
        int mid = (l + r) >> 1, res = -inf;
        if (ql <= mid)
            res = std::max(res, lc->qmax(ql, qr, l, mid));
        if (qr > mid)
            return std::max(res, rc->qmax(ql, qr, mid + 1, r));
        return res;
    }
} pool[N * 4], *curr = pool, *segt;
SegT *build(const int l, const int r) {
    if (l == r)
        return new (curr++) SegT((int)io);
    int mid = (l + r) >> 1;
    SegT *lc = build(l, mid);
    return new (curr++) SegT(lc, build(mid + 1, r), r - l + 1);
}
int main() {
    static int m, opt, l, r;
    n = io;
    segt = build(1, n);
    m = io;
    while (m--) {
        opt = io;
        l = io;
        r = io;
        switch (opt) {
            case 1: segt->uadd(l, r, io); break;
            case 2: segt->umax(l, r, io); break;
            case 3: segt->umin(l, r, io); break;
            case 4: io.print(segt->qsum(l, r)); break;
            case 5: io.print(segt->qmax(l, r)); break;
            default: io.print(segt->qmin(l, r));
        }
    }

    return 0;
}
