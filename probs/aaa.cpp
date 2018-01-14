#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
const int M = 500010;
struct flower {
    int s, c, m, sum, ans, id;
    inline void init() {
        scanf("%d%d%d", &s, &c, &m);
        sum = 1;
        ans = 0;
    }
}t[M], p[M], t1[M], t2[M];
int n, pn=0, k;
inline bool cmp1(flower a, flower b) {
    return a.s < b.s || (a.s == b.s && a.c < b.c) || (a.s == b.s && a.c == b.c && a.m < b.m);
}
inline bool cmp2(flower a, flower b) {
    return a.c < b.c || (a.c == b.c && a.id < b.id);
}
struct BIT {
    int n, c[M<<2];
    inline void init(int _n) {
        n = _n;
        memset(c, 0, sizeof(c));
    }
    inline int lb(int x) {return x&(-x);}
    inline void add(int x, int d) {
        for (; x<=n; x+=lb(x)) c[x] += d;
    }
    inline int ask(int x) {
        int ret=0;
        for (; x; x-=lb(x)) ret += c[x];
        return ret;
    }
}T;
// j<i, cj<=ci, mj<=mi
inline void cdq(int l, int r) {
    if(l == r) return;
    int mid = l+r >> 1;
    for (int i=l; i<=r; ++i) {
        if(p[i].id <= mid) T.add(p[i].m, p[i].sum);
        else p[i].ans += T.ask(p[i].m);
    }
    for (int i=l; i<=r; ++i) 
        if(p[i].id <= mid) T.add(p[i].m, -p[i].sum);
    int t1n, t2n;
    t1n = t2n = 0;
    for (int i=l; i<=r; ++i)
        if(p[i].id <= mid) t1[++t1n] = p[i];
        else t2[++t2n] = p[i];
    int tn = l-1;
    for (int i=1; i<=t1n; ++i) p[++tn] = t1[i];
    for (int i=1; i<=t2n; ++i) p[++tn] = t2[i];
    cdq(l, mid);
    cdq(mid+1, r);
}
int ans[M];
int main() {
    scanf("%d%d", &n, &k);
    for (int i=1; i<=n; ++i) t[i].init();
    sort(t+1, t+n+1, cmp1);
    p[++pn] = t[1];
    for (int i=2; i<=n; ++i) {
        if(t[i].s != t[i-1].s || t[i].c != t[i-1].c || t[i].m != t[i-1].m) p[++pn] = t[i];
        else p[pn].sum ++;
    }
    for (int i=1; i<=pn; ++i) p[i].id = i, p[i].ans += p[i].sum - 1;
    T.init(k);
    sort(p+1, p+pn+1, cmp2);
    cdq(1, pn); 
    for (int i=1; i<=pn; ++i) ans[p[i].ans] += p[i].sum;
    for (int i=0; i<n; ++i) printf("%d\n", ans[i]);
    return 0;
}
