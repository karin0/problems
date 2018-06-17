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

const int N = 200002;
int n, seq[N];
void chmin(int &x, const int v) {
    x = std::min(x, v);
}
struct SegT {
    SegT *lc, *rc;
    int x;
    SegT() {}
    SegT(const int _x) : x(_x) {}
    SegT(SegT *_l, SegT *_r) : lc(_l), rc(_r), x(INT_MAX) {}
    void umin(const int ql, const int qr, const int v, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return chmin(x, v);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->umin(ql, qr, v, l, mid);
        if (qr > mid)
            rc->umin(ql, qr, v, mid + 1, r);
    }
    int query(const int qi, const int l = 1, const int r = n) {
        if (l == r)
            return x;
        int mid = (l + r) >> 1;
        if (qi <= mid)
            return std::min(x, lc->query(qi, l, mid));
        else
            return std::min(x, rc->query(qi, mid + 1, r));
    }
} pool[N * 2], *curr = pool, *segt;
SegT *build(const int l, const int r) {
    if (l == r)
        return new (curr++) SegT(seq[l]);
    int mid = (l + r) >> 1;
    return new (curr++) SegT(build(l, mid), build(mid + 1, r));
}
struct Query {
	int l, r, *ans;
	bool operator < (const Query &rh) const {
		return l < rh.l;
	}
} qwq[N];
int main() {
    static int a[N], pos[N], nxt[N], ans[N], m, i, x, y, cur = 1;
    n = io;
    m = io;
    rep (i, 1, n) {
        x = io;
        nxt[i] = n + 1;
        if (pos[x])
            nxt[pos[x]] = i;
        pos[a[i] = x] = i;
        while (pos[y])
            ++y;
        seq[i] = y;
    }
    segt = build(1, n);
    rep (i, 1, m) {
        Query &q = qwq[i];
        q.l = io, q.r = io, q.ans = &ans[i];
    }
    std::sort(qwq + 1, qwq + m + 1);
    rep (i, 1, m) {
        const Query &q = qwq[i];
        while (cur < q.l) {
            segt->umin(cur + 1, nxt[cur] - 1, a[cur]);
            ++cur;
        }
        *q.ans = segt->query(q.r);
    }
    rep (i, 1, m)
        io.print(ans[i]);
    return 0;
}

