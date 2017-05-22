#include <iostream>
#include <algorithm>
using namespace std;

int comp(int a, int b) {
    return a>b;
}
int main(){
    ios::sync_with_stdio(false);
    int n, s[110], cpos=0, ans=0;
    cin >> n;
    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        s[cpos]=x;
        cpos++;
    }
    sort(s, s+n, comp);
    for (int j=0; j<n; j++) {
        bool success = false;
        for (int k=j+1; k<n; k++) {
            int tg=s[j]-s[k];
            for (int l=k+1; l<n; l++) {
                if (s[l]==tg) {
                    success=true;
                    break;
                }
            }
            if (success) break;
        }
        if (success) ans+=1;
    }
    cout << ans;
    return 0;
}