/*
hihoCoder 1078
AC
线段树;区间更新;模板
*/
#include <cstring>
#include <cstdio>
#define FA(x) ((x)>>1)
#define LC(x) ((x)<<1)
#define RC(x) (((x)<<1)|1)
//#define BRO(x) (((x)&1)?((x)-1):((x)|1)) 
using namespace std;
const int MAXN=100010;
const int MAXC=MAXN<<2;
int n;
int p[MAXN], st[MAXC], lazy[MAXC];

void build(int k, int l, int r) {
    if (l==r) {
        st[k]=p[l];
        return;
    }
    build(LC(k), l, l+((r-l)>>1));
    build(RC(k), l+((r-l)>>1)+1, r);
    st[k]=st[LC(k)]+st[RC(k)];
}

void unlazy(int k, int l, int r) {
    if (lazy[k]>=0) {
        lazy[LC(k)]=lazy[k];
        st[LC(k)]=lazy[k]*(((r-l)>>1)+1);
        lazy[RC(k)]=lazy[k];
        st[RC(k)]=lazy[k]*(r-l-((r-l)>>1));
        lazy[k]=-1;
    }
}

void update(int k, int l, int r, int x, int y, int v) {
    if (y<l || r<x) return;
    if (x<=l && r<=y) {
        st[k]=v*(r-l+1);
        lazy[k]=v;
        return;
    }
    unlazy(k, l, r); // Unlazy the node if it would be updated
    update(LC(k), l, l+((r-l)>>1), x, y, v);
    update(RC(k), l+1+((r-l)>>1), r, x, y, v);
    st[k]=st[LC(k)]+st[RC(k)];
}

int query(int k, int l, int r, int x, int y) {
    if (y<l || r<x) return 0;
    if (x<=l && r<=y) return st[k];
    unlazy(k, l, r);
    return query(LC(k), l, l+((r-l)>>1), x, y) + query(RC(k), l+1+((r-l)>>1), r, x, y);
}

#ifdef AKARI
void printSt(int s, int l) {
    bool is_empty=true;
    for (int i=0; i<l; i++) {
        printf("%d ", st[i+l]);
        if (st[i+l]!=0) is_empty=false;
    }
    printf("\n");
    if (!is_empty) printSt(s+l, l*2);
}
#endif
int q;
int new_p;
int oper, x, y;
int main() {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        scanf("%d", p+i);
    }
    build(1, 1, n);
    memset(lazy, -1, sizeof(int)*(n<<2));
    scanf("%d", &q);
    while (q--) {
        //printSt(1, 1);
        scanf("%d%d%d", &oper, &x, &y);
        if (oper) { // update
            scanf("%d", &new_p);
            update(1, 1, n, x, y, new_p); // not completed
        } else { // query
            printf("%d\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}
