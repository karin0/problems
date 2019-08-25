#include <bits/stdc++.h> 
using namespace std;
#define N 101010
// #define int long long
int a[N];
int main(){
    int T;
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>T;
    while(T--){
        int n,k;
        cin>>n>>k;
        int i;
        long long x=0;
        for(i=1;i<=n;i++){
            cin>>a[i];
            x+=a[i]/k;
            a[i]%=k;
        }
        sort(a+1,a+1+n);
        //int y=max(0LL,n-1-x);
        long long ans=(long long)n*k;
        long long t = min(x + 1, (long long)n);
        for(i=1;i<=t;i++){
            ans+=a[i];
        }
        ans+=max(0LL,(x+1-n))*k;
        cout<<ans<<endl;
    }
    
    return 0;
}