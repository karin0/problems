#include <iostream>
#include <set>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int n, ans=0;
    cin>>n;
    int T[n+10];
    int pos[n+10];
    for (int i = 1; i <= n; i++) {
        cin >> T[i];
        pos[i]=i;
    }

    while (true) {
        bool finish=false;
        ans++;
        for (int j = 1; j <= n; j++) {
            pos[j]=T[pos[j]];
            if (pos[j]==j) {
                finish=true;
                break;
            }
        }
        if (finish) break;
    }
    cout << ans;
    return 0;
}