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

const int mo = 19940417;
const ll inv2 = 9970209, inv6 = 3323403;
int mck(const int x) {
    return x >= mo ? x - mo : x;
}
int mck2(const int x) {
    return x < 0 ? x + mo : x;
}
int sum1(const int l, const int r) {
    return inv2 * (l + r) % mo * (r - l + 1) % mo;
}
int _sum2(const ll n) {
    return n * (n + 1) % mo * (2 * n + 1) % mo;
}
int sum2(const int l, const int r) {
    return mck2(_sum2(r) - _sum2(l - 1)) * inv6 % mo;
}
int calc(int n) {
    static int i, ni, x, res;
    for (res = 0, i = 1; i <= n; i = ni + 1) {
        x = n / i;
        ni = n / x;
        res = (res + (ll)x * sum1(i, ni)) % mo; // ll here
    }
    return res;
}
int calc(int n, int k) {
    static int i, ni, x, res;
    for (res = 0, i = 1; i <= n; i = ni + 1) {
        x = k / i;
        ni = std::min(n, k / x);
        res = (res + (ll)x * sum1(i, ni)) % mo; // ll here
    }
    return res;
}

int main() {
    static int n, m, i, ni, t, x, y, ans;
    n = io;
    m = io;
    if (n > m)
        std::swap(n, m);
    t = mck2((ll)m * (m - 1) % mo - calc(m));
    ans = mck2(mck((ll)n * n % mo * t % mo + (ll)n * calc(n, m) % mo) - (ll)t * calc(n) % mo);
    for (i = 1; i <= n; i = ni + 1) {
        x = n / i;
        y = m / i;
        ni = std::min(n / x, m / y);
        ans = mck2(ans - (ll)sum2(i, ni) * x % mo * y % mo);
    }
    io.print(ans);

    return 0;
}

