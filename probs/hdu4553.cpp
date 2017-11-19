/*
HDU 4553
TLE

*/
#include <cstring>
#include <cstdio>
#include <algorithm>
#define FA(x) ((x)>>1)
#define LC(x) ((x)<<1)
#define RC(x) (((x)<<1)|1)
#define MID(x,y) ((x)+(((y)-(x))>>1))
#define Q_1 'D'
#define Q_2 'N'
#define Q_3 'S'
#define A_1_ACC_AT "%d,let's fly\n"
#define A_1_DEN "fly with yourself\n"
#define A_2_ACC_AT "%d,don't put my gezi\n"
#define A_2_DEN "wait for me\n"
#define A_3 "I am the hope of chinese chengxuyuan!!\n"
using namespace std;
const int MAXN=100010;
int n, st[MAXN<<2], lazy[MAXN<<2];

void unlazy(int k, int l, int r) {
    if (lazy[k]!=-1) {
        lazy[LC(k)]=lazy[k];
        lazy[RC(k)]=lazy[k];
        st[LC(k)]=lazy[k];
        st[RC(k)]=lazy[k];
        lazy[k]=-1;
    }
}

void update(int k, int l, int r, int x, int y, int s) {
    if (y<l || r<x) return;
    if (x<=l && r<=y) {
        st[k]=s;
        lazy[k]=s;
        return;
    }
    unlazy(k, l, r);
    update(LC(k), l, MID(l, r), x, y, s);
    update(RC(k), MID(l, r)+1, r, x, y, s);
    st[k]=max(st[LC(k)], st[RC(k)]); // Proirity
}


int query(int k, int l, int r, int x, int y) {
    if (y<l || r<x) return 0;
    if (x<=l && r<=y) return st[k];
    unlazy(k, l, r);
    return max(query(LC(k), l, MID(l, r), x, y), query(RC(k), MID(l, r)+1, r, x, y));
}

int end_pos, target, res, worse_i;
int locate(int len, bool vip) {
    end_pos=n-len+1;
    worse_i=0;
    for (int i=1; i<end_pos; ++i) {
        res=query(1, 1, n, i, i+len-1);
        if (res==0) return i;
        if ((!worse_i) && res==1) worse_i=i;
    }
    return vip ? worse_i : 0;
}

int c_case, q, a, b, located_pos;
char oper[15];
int main() {
    scanf("%d", &c_case);
    for (int n_case=1; n_case<=c_case; ++n_case) {
        printf("Case %d:\n", n_case);
        scanf("%d%d", &n, &q);
        memset(lazy, -1, sizeof(int)*(n<<2));
        memset(st, 0, sizeof(int)*(n<<2));
        // Need not to build!
        while (q--) {
            scanf("%s%d", oper, &a);
            if (oper[0]==Q_1) { // For DS
                 located_pos=locate(a, false);
                 if (located_pos) {
                     printf(A_1_ACC_AT, located_pos);
                     update(1, 1, n, located_pos, located_pos+a-1, 1);
                 } else
                     printf(A_1_DEN);
            } else if (oper[0]==Q_2) {
                located_pos=locate(a, true);
                if (located_pos) {
                    printf(A_2_ACC_AT, located_pos);
                    update(1, 1, n, located_pos, located_pos+a-1, 2);
                } else
                    printf(A_2_DEN);
            } else {
                scanf("%d", &b);
                printf(A_3);
                update(1, 1, n, a, b, 0);
            }
        } 
    }
    return 0;
}
