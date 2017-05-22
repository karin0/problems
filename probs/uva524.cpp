/*
UVa 524 (SA Codevs 1031)
AC
回溯
*/
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

const int MAXN=20;

int n, cse=0, ring[MAXN+10], known=3;
bool isprime[2*MAXN+10], used[MAXN+10];
void dfs(int pos){
    if (pos==n) {
        if (isprime[ring[n-1]+1]) {
            // Success
            for (int i=0; i<n-1; i++) {
                printf("%d ", ring[i]);
            }
            printf("%d\n", ring[n-1]);
        }
        return;
    }
    for (int i=2; i<=n; i++) {
        if (!used[i]&&isprime[ring[pos-1]+i]) {
            used[i]=true;
            ring[pos]=i;
            dfs(pos+1);
            used[i]=false;
            //ring[pos]=0; // Need not!
        }
    }
}

int main(){
    for (int i=0; i<2*MAXN+10; i++) isprime[i]=true;
    while (true) {
        if (scanf("%d", &n)==EOF) break:
        if (cse!=0) printf("\n");
        cse++;
        printf("Case %d:\n", cse);

        //int req=2*n+10;
        int req=2*MAXN; // For n <= 16 in UVa & Remember to 2x
        if (req>known) {
            // Make primes table
            for (int i=2; i<=(int)(sqrt(req)+0.5); i++) {
                if (isprime[i]) {
                    for (int j=i*i; j<=req; j+=i) {
                        isprime[j]=false;
                    }
                }
            }
            known=req;
        }
        memset(ring, 0, sizeof(ring));
        memset(used, false, sizeof(used));
        ring[0]=1; used[1]=true;
        dfs(1);
    }
    
    return 0;
}
