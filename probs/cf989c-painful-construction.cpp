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

const int n = 40, m = 50, h = 10;
int a[55][55];
int main() {
    static int i, j, k, q, c[5];
    rep (i, 1, 4)
        c[i] = (int)io - 1;
    rep (k, 1, 4) {
        re (i, (k - 1) * h, k * h)
            re (j, 0, m)
                a[i][j] = k;
    }
    rep (k, 1, 4) {
        q = k > 2 ? k - 2 : (k + 2);
        for (i = (k - 1) * h; i < k * h; i += 2) {
            for (j = 1; j < m - 1; j += 2) {
                if (!c[q])
                    goto ex;
                a[i][j] = q;
                --c[q];
            }
        }
ex:
        // assert(c[q] == 0);
        2333;
    }
    io.print(n, ' ');
    io.print(m);
    re (i, 0, n) {
        re (j, 0, m)
            io.pc(a[i][j] - 1 + 'A');
        io.pc('\n');
    }

    return 0;
}

