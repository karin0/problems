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
typedef unsigned long long ull;

const int N = 200001, L = 10000000, K = 50, mo = 998244353;
const int hmo = 10000141, bse = 7;

struct Node {
    Node *nxt;
    ull ha;
    int cnt;
    Node() {}
    Node(Node *_n, ull _v) : nxt(_n), ha(_v), cnt(1) {}
} *ht[hmo], pool[N * K + K * K * 500], *curr = pool;
void ins(const ull ha) {
    Node *&h = ht[ha % hmo];
    for (Node *o = h; o; o = o->nxt)
        if (o->ha == ha)
            return (void)(++o->cnt);
    h = new (curr++) Node(h, ha);  // rule #20
}
void del(const ull ha) {
    for (Node *o = ht[ha % hmo]; o; o = o->nxt)
        if (o->ha == ha)
            return (void)(--o->cnt);
}
int qry(const ull ha) {
    for (Node *o = ht[ha % hmo]; o; o = o->nxt)
        if (o->ha == ha)
            return o->cnt;
    return 0;
}

char s[L], val[N];
int pre[N], nxt[N];
ull pw[K + 3];
int main() {
    static int n, m, x, y, i, j, p, q, op;
    static ull ha, hi, ans;
    n = io;
    m = io;
    rep (i, 1, n)
        ins(val[i] = io);
    pw[0] = 1;
    rep (i, 1, K)
        pw[i] = pw[i - 1] * bse;
    while (m--) {
        op = io;
        if (op == 3) {
            io.gs(s);
            p = (int)io - 1;
            ans = 1;
            ha = 0;
            for (i = 0; s[i]; ++i) {
                s[i] -= '0';
                ha = ha * bse + s[i];
                if (i >= p) {
                    ans = ans * qry(ha) % mo;
                    if (!ans)
                        break;
                    ha -= s[i - p] * pw[p];
                }
            }
            io.print(ans);
        } else {
            x = io;
            if (op == 1) {
                y = io;
                nxt[x] = y;
                pre[y] = x;
                hi = 0;
                for (p = x, i = 1; p && i < K; ++i, p = pre[p]) {
                    ha = (hi += pw[i - 1] * val[p]);
                    for (q = y, j = i + 1; q && j <= K; ++j, q = nxt[q]) // miao a
                        ins(ha = ha * bse + val[q]);
                }
            } else {
                y = nxt[x];
                nxt[x] = pre[y] = 0;
                hi = 0;
                for (p = x, i = 1; p && i < K; ++i, p = pre[p]) {
                    ha = (hi += pw[i - 1] * val[p]);
                    for (q = y, j = i + 1; q && j <= K; ++j, q = nxt[q])
                        del(ha = ha * bse + val[q]);
                }
            }
        }
    }

    return 0;
}

