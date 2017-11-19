/*
Codevs 1430
PD
埃筛法
*/
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;

int main(){
    int n;
    scanf("%d", &n);

    // Make table
    bool isprime[n+10];
    for(int i=0; i<=n+10; i++) isprime[i]=true;

    isprime[0]=isprime[1]=false;
    for (int i=2; i<=(int)(sqrt(n)+0.5); i++) {
        if (isprime[i]) {
            for (int j=i*i; j<=n; j+=i) {
                isprime[j]=false;
            }
        }
    }
    // Completed
    
    printf(isprime[n]?"\\t":"\\n");
}
