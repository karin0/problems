#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#define forn(__e,__u) for(Edge *__e=__u->e;__e;__e=__e->e)
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
struct IO{static cint L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return s==t?EOF:*s++;}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(cchar ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,cchar end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(cchar*st,cchar end='\n'){while(*st)pc(*st++);if(end)pc(end);}void pd(cint x){pc('0'+x);pc('\n');}}io;

const int N = 200003;
ll a[N], ss[N], k, ans;
int n, nxt[N];
ll sum(int l, int r) {
    return ss[l] - ss[r + 1];
}
int main() {
    static int i, llp;
    n = io; k = io;
    rep (i, 1, n) {
        a[i] = io;
        if (a[i] > 1) {
            nxt[llp] = i;
            llp = i;
        }
    }
    nxt[llp] = n + 1;
    llp = n + 1;
    per (i, n, 1) {
        if (a[i] == 1)
            nxt[i] = llp;
        else 
            llp = i;
    }
    ss[n + 1] = 0;
    per (i, n, 1)
        ss[i] = ss[i + 1] + a[i];

    static ll p, s, lim, lp;
    static int j, lj;
    rep (i, 1, n) {
        p = 1;
        lim = k * ss[i];
        if (a[i] == 1) {
            j = nxt[i];
            lj = i;
            if (k == 1)
                ++ans;
        } else
            j = i, lj = 0;
        for (; j; j = nxt[j]) {
            ccc(i); ccf(j);
            lp = p;
            if (j <= n) {
                s = sum(i, j);
                if (lj && lj < j - 1) {
                    ccf(lp);
                    if (k * sum(i, lj) < lp && lp < k * s && lp % k == 0 && lp / k - sum(i, lj) <= j - lj - 1)
                        ++ans, ccf("++1");
                }

                if (p > lim / a[j])
                    break;
                p = p * a[j];
                ccc(p); ccf(s);
                if (p == k * s)
                    ++ans, ccf("++!");

            } else if (lj && a[n] == 1) {
                if (k * sum(i, lj) < lp && lp <= k * sum(i, n) && lp % k == 0 && lp / k - sum(i, lj) <= n - lj)
                    ++ans, ccf("++2");
            }
            lj = j;
        }
    }
    io.print(ans);

    return 0;
}

