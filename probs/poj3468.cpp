/*
POJ 3468
AC
线段树;区间更新;模板
2625ms;5292K
*/
#include <cstdio>
#define FA(x) ((x)>>1)
#define LC(x) ((x)<<1)
#define RC(x) ((x)<<1|1)
#define MID(x,y) ((x)+(((y)-(x))>>1))
using namespace std;
typedef long long LL;
const int MAXN=100010;
const int MAXC=MAXN<<2;

int n;
LL st[MAXC], lazy[MAXC], init_v[MAXN];

void build(int k, int l, int r) {
    if (l==r) {
        st[k]=init_v[l];
        return;
    } 
    build(LC(k), l, MID(l, r));
    build(RC(k), MID(l, r)+1, r);
    st[k]=st[LC(k)]+st[RC(k)];
}
void unlazy(int k, int l, int r) {
    if (lazy[k]!=0) { // Value of Lazy is the delta, therefore 0 means unset or hontou no 0
        lazy[LC(k)]+=lazy[k]; // Must use += instead of =
        lazy[RC(k)]+=lazy[k];
        st[LC(k)]+=lazy[k]*(MID(l, r)-l+1); // length of LC is MID(l, r) + 1
        st[RC(k)]+=lazy[k]*(r-MID(l, r));
        lazy[k]=0;
    }
}
void update(int k, int l, int r, int x, int y, int dv) {
    if (r<x || y<l) return;
    if (x<=l && r<=y) {
        st[k]+=dv*(r-l+1);
        lazy[k]+=dv;
        return;
    }
    unlazy(k, l, r); // unlazy if lower node would be updated!
    update(LC(k), l, MID(l, r), x, y, dv);
    update(RC(k), MID(l, r)+1, r, x, y, dv);
    st[k]=st[LC(k)]+st[RC(k)];
}
LL query(int k, int l, int r, int x, int y) {
    if (r<x || y<l) return 0;
    if (x<=l && r<=y) return st[k];
    unlazy(k, l, r);
    return query(LC(k), l, MID(l, r), x, y) + query(RC(k), MID(l, r)+1, r, x, y);
}
int q, a, b;
char oper;
LL dv;
int main() {
    scanf("%d%d", &n, &q);
    for (int i=1; i<=n; ++i) {
        scanf("%lld", init_v+i);
    }
    build(1, 1, n);
    while (q--) {
        scanf("%s%d%d", &oper, &a, &b);
        if (oper=='C') {
            scanf("%lld", &dv);
            if (dv) update(1, 1, n, a, b, dv);
        } else {
            printf("%lld\n", query(1, 1, n, a, b));
        }
    }
    return 0;
}
