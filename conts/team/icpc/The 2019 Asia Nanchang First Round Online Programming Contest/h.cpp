#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
using namespace std;
const int mm=998244353;
//const long long p1=473844410;
//const long long p2=524399943;
const long long p1=262199970;
const long long p2=736044380;

long long ksm(long long a,long long p){
    long long ret=1;
    for(;p;p>>=1,a=a*a%mm){
        if(p&1)ret=ret*a%mm;
    }
    return ret;
}

int Q;
long long ans,lastans,N;

long long inv;
void calc(){
    if(N==0){
        lastans=0;return;
    }
    long long t1=p2*ksm(3+p1,N-1)%mm;
    long long t2=p1*ksm(3+p2,N-1)%mm;
    lastans=(t1-t2+mm)*inv%mm;
}

int main(){
    scanf("%d%lld",&Q,&N);
    inv=ksm(p2-p1,mm-2);
    for (int i = 1; i <= Q;++i) {
        long long ola = lastans;
        calc();
        ans^=lastans;
        if (lastans == ola) {
            int lf = Q - i;
            if (lf & 1)
                ans ^= lastans;
            break;
        }
        N^=(lastans*lastans);
        // int nn = N;
        // if (s.count(nn))
        //    return printf("!! %d %d\n", Q, nn), 0;
        // printf("%d: %lld %lld\n", i, lastans, ans);
    }
    printf("%lld\n",ans);
    return 0;
}