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

const int g = 11000;
int main() {
    static int i, j, n, p, x, dd, a[3000], det[8000], c1, c2;
    static char s[3000];
    n = io;
    p = n - (int)io;
    io.gs(s + 1);
    rep (i, 1, n) {
        if (s[i] == '.')
            a[i] = g + i;
        else
            a[i] = s[i] - '0';
        det[i] = 0;
    }
    bool ok = 0;
    rep (i, 1, p) {
        c1 = a[i];
        c2 = a[n - p + i];
        ccc(i); ccc(n-p+1); ccc(c1); ccf(c2);
        if (c1 > c2)
            std::swap(c1, c2);
        if (c2 > g) {
            if (c1 > g) {
                det[c1 - g] = 1;
                det[c2 - g] = 0;
            } else
                det[c2 - g] = c1 ^ 1;
            ok = true;
            break;
        } else if (c1 != c2) {
            ok = true;
            break;
        }
    }
    /*
    } /else {
        rep (i, 1, p) {
            c1 = a[i];
            c2 = a[n - p + i];
            if (c1 > c2)
                std::swap(c1, c2);
            if (c2 > n) {
                if (c1 > n) {
                    x = i;
                    while (true) {
                        if (x > n) {
                            dd = 0;
                            break;
                        }
                        if (a[x] <= n) {
                            dd = a[x];
                            break;
                        }
                        x = n - p + x;
                    } 
                    det[c1] = 0;
                    det[c2] = 1;
                } else
                    det[c2] = c1 ^ 1;
                ok = true;
            } else if (c1 != c2)
                ok = true;
        }
    }*/
    if (ok) {
        rep (j, 1, n) {
            if (a[j] > g)
                io.pc('0' + det[j]);
            else
                io.pc('0' + a[j]);
        }
        io.pc('\n');
    } else
        io.ps("No");
    return 0;
}

