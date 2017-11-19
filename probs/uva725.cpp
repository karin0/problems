/*
UVa 725
AC
简单枚举
*/
#include <cstdio>
using namespace std;

// i / j = n

bool checker[12];
bool cins(char n){
    int dig;
    if (n=='\0') dig=0;
    else dig=n-'0';
    if (checker[dig]) return false; // Already one
    checker[dig]=true;
    return true;
}
int main(){
    int n=810;
    bool fst=true;
    while (true) {
        scanf("%d", &n);
        if (!n) break;
        if (!fst) printf("\n"); fst=false; // UVa does not allow ending with newline

        bool suc=false;
        for (int j=1234; j<=98765/n; j++) { // Output is sorted by order
            int i=n*j;
            for (int k=0; k<=9; k++) checker[k]=false;
            char si[8], sj[8];
            sprintf(si, "%d", i);
            sprintf(sj, "%d", j);
            for (int k=0; k<=4; k++) {
                if (!cins(si[k])) goto _sad;
                if (!cins(sj[k])) goto _sad;
            }
            suc=true;
            printf("%05d / %05d = %d\n", i, j, n); // Forward leading zero
            _sad:;
        }
        if (!suc) printf("There are no solutions for %d.\n", n);
    }

    return 0;
}
