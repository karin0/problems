#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

int n, G[300], f1[300][300], f2[300][300], s[300][300], ans1=-2000000000, ans2=2000000000;
// Max: f1[i][j]=max{f1[i][k]+f1[k+1][j]}
// Min: f2[i][j]=min{f2[i][k]+f2[k+1][j]}
// k in (i, j)

int main(){
    for (int i=0; i<=300; i++) {
        for (int j=0; j<=300; j++) {
            f2[i][j]=2000000000;
        }
    }
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%d", G+i);
        G[n+i]=G[i];
    }
    for (int i=0; i<2*n; i++) {
        for (int j=i+1; j<2*n; j++) {
            if (i+1==j) {
                s[i][j]=G[i]+G[j];
                continue;
            }
            s[i][j]=s[i][j-1]+G[j];
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<2*n-i; j++) {
            if (i==0) {
                f1[j][j]=0;
                f2[j][j]=0;
                continue;
            } else if (i==1) {
                f1[j][j+1]=G[j]+G[j+1];
                f2[j][j+1]=G[j]+G[j+1];
                continue;
            }
            for (int k=0; k<i; k++) {
                f1[j][j+i]=max(f1[j][j+i], f1[j][j+k]+f1[j+k+1][j+i]+s[j][j+i]);
                f2[j][j+i]=min(f2[j][j+i], f2[j][j+k]+f2[j+k+1][j+i]+s[j][j+i]);
            }
        }
    }
    // complete ditui
    for (int i=0; i<n; i++) {
        ans1=max(ans1, f1[i][i+n-1]);
        ans2=min(ans2, f2[i][i+n-1]);
    }
    printf("%d\n%d\n", ans2, ans1);
    return 0;
}