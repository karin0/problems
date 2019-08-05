/*
HDU 1754
WA?

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
int st[MAXN*4]; // 1 .. // For max. // [a, b]


void build(int k) {
    if (k>=n) return; // leaf
    build(LC(k)); // Do not use a global address to store LC or RC or it can be accessed before re-assigned in recursion
    build(RC(k));
    st[k]=max(st[LC(k)], st[RC(k)]);
}

void update(int k, int a) {
    k+=n-1;
    st[k]=a;
    while (k>0) {
        k=FA(k);
        st[k]=max(st[LC(k)], st[RC(k)]);
    }
}

int query(int k, int l, int r, int x, int y) {
    if (x<=l && r<=y) return st[k];
    if (l>y || r<x) return -INF;
    return max(query(LC(k), l, l+(r-l)/2, x, y), query(RC(k), l+(r-l)/2+1, r, x, y));
}

#ifdef AKARI
void printSt() {
    int k=1;
    while (k<=2*n-1) {
        //int sn1=n-k;
        //int sn2=sn1;
        //while (sn1--) printf(" ");
        for (int i=k; i<=2*k-1; ++i) printf("%d ", st[i]);
        //while (sn2--) printf(" ");
        k=2*k;
        printf("\n");
    }
}
#endif
int m, ano_n=1, tmp, x, y;
char oper;
int main() {
    while (scanf("%d%d", &n, &m)!=EOF) {
        fill(st, st+4*n, -INF);
        while (ano_n<n) ano_n<<=1;
        swap(ano_n, n);
        for (int i=1; i<=ano_n; ++i) {
            scanf("%d", st+n-1+i);
        }
        build(1);
        while (m--) {
            #ifdef AKARI
            printSt();
            #endif
            scanf("%s%d%d", &oper, &x, &y);
            if (oper=='Q') {
                printf("%d\n", query(1, 1, n, x, y));
            } else { // U for update
                update(x, y);
            }
        }
    }
    return 0;
}
