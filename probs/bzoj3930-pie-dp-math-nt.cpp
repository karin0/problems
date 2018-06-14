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

const int mo = 1000000007;
int mck2(const int x) {
    return x < 0 ? x + mo : x;
}
int qpow(ll a, int n) {
    static ll res;
    for (res = 1; n; n >>= 1, a = a * a % mo)
        if (n & 1)
            res = res * a % mo;
    return res;
}
int cdiv(const int p, const int q) {
    static int t;
    t = p / q;
    return t * q < p ? t + 1 : t;
}
int main() {
    static int n, k, l, r, i, j, d, l0, r0, t, f[100004];
    n = io;
    k = io;
    l = io;
    r = io;
    l = cdiv(l, k);
    r /= k;
    d = r - l + 1;
    per (i, d, 1) {
        l0 = cdiv(l, i);
        r0 = r / i;
        t = r0 - l0 + 1;
        int &fi = f[i];
        fi = mck2(qpow(t, n) - t);
        for (j = i + i; j <= d; j += i)
            fi = mck2(fi - f[j]);
    }
    io.print(l == 1 ? (f[1] == mo - 1 ? 0 : (f[1] + 1)) : f[1]);

    return 0;
}

