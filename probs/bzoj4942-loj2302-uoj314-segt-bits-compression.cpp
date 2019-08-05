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
typedef unsigned long long ut;

const int N = 1000000, w = 64;
const ut A0 = 0, A1 = -1, AN = 114514, v1 = 1ull;
int n;
bool done, rr;
struct SegT {
    SegT *lc, *rc;
    ut x;
    char tag;
    SegT() {}
    SegT(SegT *_l, SegT *_r) : lc(_l), rc(_r), tag(-1) {}
    void cover(const bool v) {
        x = v ? A1 : A0;
        tag = v;
    }
    void maintain() {
        if (lc->x == A0 && rc->x == A0)
            x = A0;
        else if (lc->x == A1 && rc->x == A1)
            x = A1;
        else
            x = AN;
    }
    void push_down() {
        if (tag != -1) {
            lc->cover(tag);
            rc->cover(tag);
            tag = -1;
        }
    }
    void inp(const bool v) {
        int i; re (i, 0, w) {
            x ^= v1 << i;
            if ((x >> i & v1) != v)
                return;
        }
    }
    bool inps(const bool v, const int st) {
        int i; re (i, st, w) {
            x ^= v1 << i;
            if ((x >> i & v1) != v)
                return false;
        }
        return true;
    }
    void query(const int k, const int l = 0, const int r = n) {
        if (l + 1 == r)
            return (void)(rr = (x >> (k - l * w)) & v1);
        if (x == A0)
            return (void)(rr = 0);
        if (x == A1)
            return (void)(rr = 1);
        push_down();
        int mid = (l + r) >> 1;
        if (k < mid * w)
            lc->query(k, l, mid);
        else
            rc->query(k, mid, r);
    }
    void flip(int k, const int l = 0, const int r = n) {
        // ccc(k); ccc(l); ccc(r); ccf(x);
        if (l + 1 == r) {
            k -= l * w;
            // ccf(k);
            x ^= v1 << k; // ********
            rr = x >> k & v1;
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (k < mid * w)
            lc->flip(k, l, mid);
        else
            rc->flip(k, mid, r);
        maintain();
    }
    void do_first(const bool v, const int l, const int r) {
        if (done)
            return;
        /*if (an)   // focus here. if (an) does not mean if (x == an). we are always doing this thing.
            return cover(v); */
        if (l + 1 == r) {
            inp(v);
            done = true;
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (lc->x == (v ? A0 : A1))
            lc->cover(v), rc->do_first(v, mid, r); // ***
        else
            lc->do_first(v, l, mid);
        maintain();
    }
    void q_first(const int qi, const bool v, const int st, const int l = 0, const int r = n) {
        if (l + 1 == r) {
            rr = inps(v, st);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (qi < mid)
            lc->q_first(qi, v, st, l, mid);
        else
            rc->q_first(qi, v, st, mid, r);
        maintain();
    }
    void first(const int ql, const int qr, const bool v, const int l = 0, const int r = n) {
        if (done)
            return;
        if (ql <= l && r <= qr) {
            if (x == (v ? A0 : A1))  // ***
                cover(v);
            else
                do_first(v, l, r); //  assert(done);
            return;
        }
        push_down();
        int mid = (l + r) >> 1;
        if (ql < mid) {
            lc->first(ql, qr, v, l, mid);
            if (done)
                return maintain(); // ***
        }
        if (qr > mid)
            rc->first(ql, qr, v, mid, r);
        maintain();
    }
} pool[4 * (30 * (N + 6) / w + 3)], *curr = pool, *segt;
SegT *build(const int l, const int r) {
    if (l + 1 == r)
        return new (curr++) SegT(NULL, NULL);
    int mid = (l + r) >> 1;
    return new (curr++) SegT(build(l, mid), build(mid, r));
}
void add(int k, const bool v) {
    static int b;
    // cccc("Adding at %d\n", k);
    segt->flip(k);
    if (rr == v)
        return;
    // cccc("need it\n");
    ++k;
    b = k / w;
    done = false;
    if (b * w == k)
        segt->first(b, n, !v);
    else if (segt->q_first(b, !v, k - b * w), rr)
        segt->first(b + 1, n, !v);
    // cccc("After add %d x = %lld\n", k - 1, segt->x);
}
void update(int a, const int k) {
    static int i;
    if (a == 0)
        return;
    if (a < 0) {
        a = -a;
        for (i = 0; (a >> i); ++i)
            if (a >> i & 1)
                add(k + i, 0); // cccc("After mus %d x = %lld\n", k+i,segt->x);
    } else {
        for (i = 0; (a >> i); ++i)
            if (a >> i & 1)
                add(k + i, 1);
    }
}
// takai mountain no hana desu.
int main() {
    static int m, x, op;
    m = io;
    x = std::max(100, 30 * (m + 2)) + 100;
    n = x / w + 1;
    // ccf(n);
    x = io; x = io; x = io;
    segt = build(0, n);
    while (m--) {
        op = io;
        x = io;
        if (op == 1)
            update(x, io);
        else {
            // ccf(segt->query(x));
            segt->query(x);
            io.pc(rr ? '1' : '0');
            io.pc('\n');
        }
        // ccf(segt->x);
    }

    return 0;
}
