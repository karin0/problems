/*
Codecv 2194
AC
DFS;回溯
*/
#include <cstdio>
using namespace std;

int n, ans, count;
int G[20];
bool visx[20], visa[40], visb[40];
void dfs(int p){
    if (p==n) {
        ans++;
        if (count<3) {
            count++;
            for (int i=0; i<n; i++) {
                printf("%d", G[i]+1);
                if (i!=n-1) printf(" ");
            }
            printf("\n");
        }
        return;
    };
    for (int i=0; i<n; i++) {
        if (!visx[i]&&!visa[p+i]&&!visb[n+p-i]) {
            visx[i]=visa[p+i]=visb[n+p-i]=true;
            G[p]=i;
            dfs(p+1);
            visx[i]=visa[p+i]=visb[n+p-i]=false;
        }
    }

}

int main(){
    scanf("%d", &n);
    dfs(0);
    printf("%d", ans);
    return 0;
}

