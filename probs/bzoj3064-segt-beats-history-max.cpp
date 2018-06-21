#include <bits/stdc++.h>
#define rep(i__,s__,t__) for((i__)=(s__);(i__)<=(t__);++(i__))
#define re(i__,s__,t__) for((i__)=(s__);(i__)<(t__);++(i__))
#define per(i__,s__,t__) for((i__)=(s__);(i__)>=(t__);--(i__))
#define pe(i__,s__,t__) for((i__)=(s__);(i__)>(t__);--(i__))
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
struct IO{static cint L=1000000;char a[L],b[L],*s,*t,*z,c;IO():z(b){}~IO(){fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}template<class T>operator T(){static T x;static bool f;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((f=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return f?-x:x;}void gs(char*q){for(c=gc();!isgraph(c);c=gc());*q++=c;for(c=gc();isgraph(c);c=gc())*q++=c;*q++=0;}char gg(){for(c=gc();!isgraph(c);c=gc());return c;}void pc(cchar q){if(z==b+L)fwrite(z=b,1,L,stdout);*z++=q;}template<class T>void operator()(T x,cchar e='\n'){static char r[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=r;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=r)pc(*--q);}if(e)pc(e);}void ps(cchar*q,cchar e='\n'){while(*q)pc(*q++);if(e)pc(e);}void pd(cint x){pc('0'+x);pc('\n');}}io;

const int N = 100005;
const ll inf = 1ll << 50ll;
using std::max;
struct Tag {
    ll a, b;
    Tag() {}
    Tag(cll _a, cll _b) : a(_a), b(_b) {}
    ll operator () (cll x) const {
        return max(x + a, b);
    }
    operator bool () const {
        return a != 0 || b > -inf;
    }
} const t0 = Tag(0, -inf);
Tag merge(const Tag &a, const Tag &b) {
    return Tag(max(-inf, a.a + b.a), max(a.b + b.a, b.b));
}
Tag max(const Tag &a, const Tag &b) {
    return Tag(max(a.a, b.a), max(a.b, b.b));
}
int n, a[N];
ll res;
struct Node {
    Node *lc, *rc;
    Tag tag, htag;
    ll mx, hmx;
    Node() {}
    Node(cint x) : tag(t0), htag(t0), mx(x), hmx(x) {}
    Node(Node *_l, Node *_r) : lc(_l), rc(_r), tag(t0), htag(t0) {
        maintain();
    }
    void maintain() {
        mx = max(lc->mx, rc->mx);
        hmx = max(lc->hmx, rc->hmx);
    }
    void push_down() {
        if (tag || htag) { // ***
            lc->cover(tag, htag);
            rc->cover(tag, htag);
            tag = htag = t0;
        }
    }
    void cover(const Tag &t, const Tag &ht) {
        htag = max(htag, merge(tag, ht));
        tag = merge(tag, t);
        hmx = max(hmx, ht(mx)); // *****
        mx = t(mx);
    }
    void update(const int ql, const int qr, const Tag &t, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return cover(t, t);
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->update(ql, qr, t, l, mid);
        if (qr > mid)
            rc->update(ql, qr, t, mid + 1, r);
        maintain();
    }
    void query_mx(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return (void)(res = max(res, mx));
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->query_mx(ql, qr, l, mid);
        if (qr > mid)
            rc->query_mx(ql, qr, mid + 1, r);
    }
    void query_hmx(const int ql, const int qr, const int l = 1, const int r = n) {
        if (ql <= l && r <= qr)
            return (void)(res = max(res, hmx));
        push_down();
        int mid = (l + r) >> 1;
        if (ql <= mid)
            lc->query_hmx(ql, qr, l, mid);
        if (qr > mid)
            rc->query_hmx(ql, qr, mid + 1, r);
    }
} *segt;
Node *build(cint l, cint r) {
    static Node pool[N * 2], *curr = pool;
    if (l == r)
        return new (curr++) Node(a[l]);
    int mid = (l + r) >> 1;
    return new (curr++) Node(build(l, mid), build(mid + 1, r));
}
int main() {
    static int m, l, r;
    static char op;
    n = io;
    rep (l, 1, n)
        a[l] = io;
    segt = build(1, n);
    m = io;
    while (m--) {
        op = io.gg();
        l = io; r = io;
        switch (op) {
            case 'Q': res = -inf;
                      segt->query_mx(l, r);
                      io((int)res); break;
            case 'A': res = -inf;
                      segt->query_hmx(l, r);
                      io((int)res); break;
            default:  segt->update(l, r, op == 'P' ? Tag(io, -inf) : Tag(-inf, io));
        }
    }

    return 0;
}
