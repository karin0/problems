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

const int N = 1000002;
struct Range {
    int l, r;
    int len() const {
        return r - l;
    }
    bool operator < (const Range &rh) const {
        return l < rh.l || (l == rh.l && r > rh.r);
    }
} a[N], b[N];
ll calc(int p, int q) {
    if (p > q)
        std::swap(p, q);
    const Range &x = b[p], &y = b[q];
    if (x.r <= y.l)
        return 0;
    return (ll)(y.r - x.l) * (x.r - y.l);
}
void chmax(ll &x, const ll v) {
    x = std::max(x, v);
}
bool chmax2(ll &x, const ll v) {
    if (v > x)
        return x = v, true;
    return false;
}
ll ans;
void dac(const int l, const int r, const int dl, const int dr) {
    if (l > r)
        return;
    int i;
    if (dl == dr) {
        rep (i, l, r)
            chmax(ans, calc(i, dl));
        return;
    }
    int mid = (l + r) >> 1, p = 0;
    int t = std::min(dr, mid - 1);
    ll f = 0;
    rep (i, dl, t)
        if (chmax2(f, calc(i, mid)))
            p = i;
    if (p)
        chmax(ans, f), dac(l, mid - 1, dl, p), dac(mid + 1, r, p, dr);
    else
        dac(l, mid - 1, dl, dr), dac(mid + 1, r, dl, dr);
}
int main() {
    static int n, cnt, i;
    // static bool flag;
    n = io;
    rep (i, 1, n) {
        a[i].l = io;
        a[i].r = io;
    }
    std::sort(a + 1, a + n + 1);
    b[cnt = 1] = a[1];
    // flag = true;
    rep (i, 2, n) {
        if (a[i].r <= b[cnt].r) {
            // if (flag)  // do not use the flag but why
            chmax(ans, (ll)b[cnt].len() * a[i].len());
            // flag = false;
        } else
            b[++cnt] = a[i]; // flag = true;
    }
    dac(2, cnt, 1, cnt);  // **
    io.print(ans);

    return 0;
}
