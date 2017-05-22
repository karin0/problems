/*
Luogu 1008
AC
简单枚举
*/
#include <cstdio>
using namespace std;

int que[3];
int main(){
    for (int i=123; i<=329; i++) {
        que[0]=i; que[1]=que[0]+i; que[2]=que[1]+i;
        bool checker[110];
        for (int j=1; j<=9; j++) checker[j]=false;
        for (int j=0; j<=2; j++) {
            int& num=que[j];
            int dig[3];
            dig[0]=num/100;
            dig[1]=(num/10)%10;
            dig[2]=num%10;
            for (int k=0; k<=2; k++) {
                if(checker[dig[k]]) goto _out;
                checker[dig[k]]=true;
                // THE WORLD!!!
            }
        }
        printf("%d %d %d\n", que[0], que[1], que[2]);
        _out:
        continue;
    }

    return 0;
}
