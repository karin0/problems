#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << x << "  "
    #define cccc(x) std::cerr << #x " = " << x << std::endl
    #define ccccc(x) std::cerr << x << std::endl
#else
    #define ccc(x) 0
    #define cccc(x) 0
    #define ccccc(x) 0
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);/*p=b;*/}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;/*return s==t?EOF:*s++;*/}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,const char end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;
typedef long long ll;

const int N = 1000004, inf = 0x3f3f3f3f;
int n, a[N];
struct BIT {
    int c[N];
    void init() {
        static int i;
        rep (i, 1, n)
            c[i] = inf;  // ******** we are not supposed to use INT_MAX
    }
    void update(int i, int x) {
        for (; i <= n; i += i & -i)
            c[i] = std::min(c[i], x);
    }
    int query(int i) {
        static int res;
        for (res = inf; i >= 1; i -= i & -i)
            res = std::min(res, c[i]);
        return res;
    }
} ds1, ds2;
int main() {
    static int i, f;
    n = io;
    if (n == 1) {
        io.print(std::abs((int)io));
        return 0;
    }
    rep (i, 1, n)
        a[i] = io;
    ds1.init();
    ds2.init();
    f = std::abs(a[n]);
    ds1.update((n + 1) - n, f + n - 1);
    ds2.update(n, f - n + 1);
    for (i = n - 1; ; --i) {
        // r1 = ds1.query(i - 1);
        // r2 = ds2.query(i - 1);
        f = std::abs(a[i] - n + i);
        if (a[i] + i + 1 <= n)
            f = std::min(f, ds1.query((n + 1) - (std::max(1, a[i] + i + 1))) - i - a[i]);
        if (a[i] + i >= 1)
            f = std::min(f, ds2.query(std::min(n, a[i] + i)) + i + a[i]);
        if (i == 1) {
            io.print(f);
            return 0;
        }
        ds1.update((n + 1) - i, f + i - 1);
        ds2.update(i, f - i + 1);
    }

    return 0;
}

// f[i] = min {f[j] + abs(i - j - 1  - a[j])}
