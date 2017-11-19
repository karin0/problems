/*
Codevs 1295
AC
DFS;回溯
*/
#include <cstdio>
using namespace std;

int n, ans;
//int G[20];
bool visx[20], visa[40], visb[40];
void dfs(int p){
    if (p==n) {ans++; return;};
    for (int i=0; i<n; i++) {
        if (!visx[i]&&!visa[p+i]&&!visb[n+p-i]) {
            visx[i]=visa[p+i]=visb[n+p-i]=true;
            //G[p]=i;
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
