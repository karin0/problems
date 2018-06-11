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

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(3, 50);
int n, m, a[55][55];
bool ok(int i, int j) {
    return 1 <= i && i <= n && 1 <= j && j <= m;
}
bool ofil(int i, int j) {
    return ok(i, j) && a[i][j];
}
bool fr(int i, int j, int c) {
    if (a[i][j])
        return false;
    if (ok(i - 1, j) && a[i - 1][j] == c)
        return false;
    if (ok(i + 1, j) && a[i + 1][j] == c)
        return false;
    if (ok(i, j - 1) && a[i][j - 1] == c)
        return false;
    if (ok(i, j + 1) && a[i][j + 1] == c)
        return false;
    return true;
}
int main() {
    static int i, j, k, c[5], tc[5], cnt[5], cs, x, tt[5], dd[5], cc;
    static char sy[] = {0, 'A', 'B', 'C', 'D'};
    c[1] = io;
    c[2] = io;
    c[3] = io;
    c[4] = io;
    cs = c[1] + c[2] + c[3] + c[4];
    while (true){
        n = dis(gen);
        m = dis(gen);
        // ccc(n); ccf(m); 
        if (cs > n * m)
            continue;
        rep (i, 1, n) rep (j, 1, m)
            a[i][j] = 0;
        rep (k, 1, 4) {
            cnt[k] = 0;
            tc[k] = c[k];
            rep (i, 1, n) rep (j, 1, m) {
                if (tc[k] == 0)
                    goto ex;
                if (fr(i, j, k))
                    a[i][j] = k, --tc[k];
            }
ex:
            if (tc[k]) {
                // ccf("ck");
                goto ex2;
            }
        }
        /*rep (i, 1, n) {
            rep (j, 1, m) { if (!a[i][j])
                putchar('?');
            else
                putchar(sy[a[i][j]]); }
            putchar('\n');
        }*/
        // break;
        rep (i, 1, n) rep (j, 1, m) if (!a[i][j]) {
            if (ok(i, j + 1) && !a[i][j + 1])
                continue;
            cc = 0;
            rep (k, 1, 4)
                tt[k] = 0;
            if (ofil(i - 1, j))
                ++tt[a[i - 1][j]], ++cc;
            else if (ofil(i + 1, j))
                ++tt[a[i + 1][j]], ++cc;
            else if (ofil(i, j - 1))
                ++tt[a[i][j - 1]], ++cc;
            else if (ofil(i, j + 1))
                ++tt[a[i][j + 1]], ++cc;
            if (cc < 3)
                continue;
            cc = 0;
            rep (k, 1, 4) if (tt[k] == 1)
                dd[++cc] = k;
            if (cc) {
                x = dis(gen) % cc + 1;
                a[i][j] = dd[x];
                continue;
            }
            //cccc("space %d\n", cc);
            goto ex2;
        }
        //ccf("okay");
        rep (j, 1, m) {
            x = 0;
            per (i, n, 1) if (a[i][j]) { 
                x = a[i][j];
                // printf("found %d for %d at %d\n", x, i, j);
                break;
            }
            if (x)
                ++cnt[x];
            else
                goto ex2;
        }
        x = 0;
        rep (i, 1, 4) if (cnt[i] == 1) {
            x = i;
            break;
        }
        if (x == 0)
            goto ex2;
        // printf("ALt %d\n", x);
        rep (i, 1, n) {
            rep (j, 1, m) if (!a[i][j])
                io.pc(sy[x]);
            else
                io.pc(sy[a[i][j]]);
            io.pc('\n');
        }
        break;
ex2:
        continue;
    }
    return 0;
}

