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

int k;
ll dp[301][301][2][2][2][2];
ll sq(const ll x) {
    return x * x;
}
ll f(int n, int m, bool w, bool a, bool s, bool d) {
    if (n > m) {
        std::swap(n, m);
        std::swap(w, a);
        std::swap(s, d);
    }
    if (w > s)
        std::swap(w, s);
    if (a > d)
        std::swap(a, d);
    ll &ans = dp[n][m][w][a][s][d];
    if (ans != 0x3f3f3f3f3f3f3f3fll)
        return ans;
    ans = sq(n * m - k);
    int i;
    if (w || s || (a && d))
        re (i, 1, n)
            ans = std::min(ans, f(i, m, w, a, s, 0) + f(n - i, m, w, 0, s, d));
    if (a || d || (w && s))
        re (i, 1, m)
            ans = std::min(ans, f(n, i, w, a, 0, d) + f(n, m - i, 0, a, s, d));
    return ans;
}
int main() {
    static int n, m;
    n = io;
    m = io;
    k = io;
    memset(dp, 0x3f, sizeof(dp));
    io.print(f(n, m, 1, 1, 1, 1));
    return 0;
}

