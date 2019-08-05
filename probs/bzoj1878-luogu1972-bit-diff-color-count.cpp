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

const int N = 50003, M = 200003, V = 1000003;  // for luogu N = 500003
int n, c[N];
void inc(int i) {
    for (; i <= n; i += i & -i)
        ++c[i];
}
void dec(int i) {
    for (; i <= n; i += i & -i)
        --c[i];
}
int qry(int i) {
    static int res;
    for (res = 0; i; i -= i & -i)
        res += c[i];
    return res;
}
struct Query {
    int l, r, *ans;
    bool operator < (const Query &rh) const {
        return l < rh.l;
    }
} qwq[M];
int main() {
    static int m, i, pos[V], nxt[N], ans[M], cur = 1;
    n = io;
    rep (i, 1, n) {
        m = io;
        if (pos[m])
            nxt[pos[m]] = i;
        else
            inc(i);
        pos[m] = i;
    }
    m = io;
    rep (i, 1, m) {
        Query &q = qwq[i];
        q.l = io;
        q.r = io;
        q.ans = &ans[i];
    }
    std::sort(qwq + 1, qwq + m + 1);
    rep (i, 1, m) {
        const Query &q = qwq[i];
        while (cur < q.l) {
            dec(cur);
            if (nxt[cur])
                inc(nxt[cur]);
            ++cur;
        }
        *q.ans = qry(q.r);
    }
    rep (i, 1, m)
        io.print(ans[i]);

    return 0;
}

