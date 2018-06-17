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

const int N = 10002, M = 502, A = 5002;
int n2, n1;
template <class T, const int L>
struct BIT {
    T c[L];
    int query2d(int i, int j) {
        int res = 0;
        for (; i >= 1; i -= i & -i)
            res = std::max(res, c[i].query1d(j));
        return res;
    }
    int query1d(int i) {
        int res = 0;
        for (; i >= 1; i -= i & -i)
            res = std::max(res, c[i]);
        return res;
    }
    void update2d(int i, int j, int v) {
        for (; i <= n2; i += i & -i)
            c[i].update1d(j, v);
    }
    void update1d(int i, int v) {
        for (; i <= n1; i += i & -i)
            c[i] = std::max(c[i], v);
    }
};
BIT<BIT<int, M>, A + M> bit;
int n, m, a[N];
int main() {
    static int i, j, ans = 1, f;
    n = io;
    m = io;
    rep (i, 1, n)
        n2 = std::max(n2, a[i] = io);
    n2 += (n1 = m + 1);
    rep (i, 1, n) per (j, m, 0) { // j: m -> 0, to prevent f[i][*] trans from f[i][*]
        ans = std::max(ans, f = 1 + bit.query2d(a[i] + j + 1, j + 1));
        bit.update2d(a[i] + j + 1, j + 1, f);
    }
    io.print(ans);

    return 0;
}
// f[i][j] = max{f[p][q]} + 1, q <= j, p <= i, a[p] + q <= a[i] + j
