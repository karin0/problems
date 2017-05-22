/*
HDU 1754
AC
线段树;RMQ;模板;单点更新
*/
#include <cstdio>
#include <algorithm>
#define FA(x) ((x)>>1)
#define LC(x) ((x)<<1)
#define RC(x) (((x)<<1)|1)
using namespace std;

const int MAXN=200010;
const int INF=2147483000;
int n;
int st[MAXN*4], score[MAXN], leaf[MAXN]; // 1 .. //For max. // [a, b]


void build(int k, int l, int r) {
    if (l==r) {
        st[k]=score[l];
        leaf[l]=k;
        return;
    }; // leaf
    build(LC(k), l, l+(r-l)/2); // Do not use a global address to store LC or RC or it can be accessed before re-assigned in recursion
    build(RC(k), l+(r-l)/2+1, r);
    st[k]=max(st[LC(k)], st[RC(k)]);
}

void updateValue(int k, int a) {
    st[k]=a;
    if (k==1) return;
    updateValue(FA(k), max(a, st[ (k&1) ? (k-1) : (k|1) ]));
}
int query(int k, int l, int r, int x, int y) {
    if (x<=l && r<=y) return st[k];
    if (l>y || r<x) return -INF;
    return max(query(LC(k), l, l+(r-l)/2, x, y), query(RC(k), l+(r-l)/2+1, r, x, y));
}

int m, x, y;
char oper;
int main() {
    while (scanf("%d%d", &n, &m)!=EOF) {
        fill(st, st+4*n, -INF);
        for (int i=1; i<=n; ++i) {
            scanf("%d", score+i);
        }
        build(1, 1, n);
        while (m--) {
            scanf("%s%d%d", &oper, &x, &y);
            if (oper=='Q') {
                printf("%d\n", query(1, 1, n, x, y));
            } else { // U for update
                updateValue(leaf[x], y);
            }
        }
    }
    return 0;
}
