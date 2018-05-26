#include <cstdio>
#include <algorithm>
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
// struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);/*p=b;*/}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;/*return s==t?EOF:*s++;*/}void gs(char*st){static char c;for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static char c;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char c){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=c;}template<class T>void print(T x,const char end='\n'){static char c[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=c;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=c)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;

typedef long long ll;

const int N = 500003, S = 20;
int a[N];
ll s[N / S + 1];
ll query(const int l, const int r) {
    int bl = l / S, br = r / S, i;
    ll res;
    if (bl == br) {
        res = 0;
        rep (i, l, r)
            res += a[i];
        return res;
    }
    res = s[br] - s[bl - 1];
    re (i, bl * S, l)
        res -= a[i];
    bl = (br + 1) * S;
    re (i, r + 1, bl)
        res -= a[i];
    return res;
}
int main() {
    static int n, m, t, i, j, c, l, r;
    static ll la;
    scanf("%d%d%d", &n, &m, &t);
    re (i, 0, n) {
        if (c >= S)
            ++j, c = 0;
        scanf("%d", &a[i]);
        s[j] += a[i];
        ++c;
    }
    rep (i, 1, j)
        s[i] += s[i - 1];
    if (t) {
        rep (i, 1, m) {
            scanf("%d%d", &l, &r);
            l = (l ^ la) % n;
            r = (r ^ la) % n;
            if (l > r)
                std::swap(l, r);
            printf("%lld\n", la = query(l, r));
            la = std::abs(la);
        }
    } else {
        rep (i, 1, m) {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(l - 1, r - 1));
        }
    }


    return 0;
}
