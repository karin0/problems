#include<bits/stdc++.h>

using namespace std;

#define int __int128

int pw(int a,int x){

    int ret=1;

    for(;x;x>>=1,a*=a)if(x&1)ret*=a;

    return ret;

}

int f(int i,int j,int a,int b){

    if(i<j)swap(i,j);

    int x=__gcd(pw(i,a)-pw(j,a),pw(i,b)-pw(j,b));

    assert(x==i-j);

    return x;

}

//#undef int 

signed main(){

    long long n,i,j,a,b;

//  while(cin>>i>>j>>a>>b){

//      cout<<f(i,j,a,b)<<' '<<i-j<<endl;

//  }

#define mod (1000000007)

    long long T; 

    cin>>T;

    while(T--){

        int ans=0;

        cin>>n>>a>>b;

        for(int i=1;i<=n;i++){

            for(int j=1;j<=i;j++){

                if(__gcd(i,j)==1){

                    (ans+=f(i,j,a,b))%=mod;

                }

            }

        }   

        cout<<(long long)ans<<endl;

    }

    

    return 0;

}