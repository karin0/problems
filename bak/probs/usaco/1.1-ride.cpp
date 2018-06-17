/*
ID: dredgar1
PROG: ride
LANG: C++
*/
/*
USACO Section 1.1 2
AC
模拟
*/
#include <cstdio>
using namespace std;

char a[12], b[12];
int sa=1, sb=1;
int main() {
    #ifndef AKARI
    freopen("ride.in", "r", stdin);
    freopen("ride.out", "w", stdout);
    #endif
    scanf("%s", a);
    scanf("%s", b);
    for (int i=0; a[i]!=0; i++) {
        sa*=a[i]-'A'+1;
    }
    for (int i=0; b[i]!=0; i++) {
        sb*=b[i]-'A'+1;
    }
    printf(sa%47==sb%47 ? "GO\n": "STAY\n");
    return 0;
}
