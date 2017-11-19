#include <iostream>
#include <cstring>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int n, x, sum=0;
    cin >> n >> x;
    for (int i=1; i<=n; i++) {
        int k=i;
        while (k) {
            if (k%10==x) sum++;
            k/=10;
        }
    }
    cout << sum;
    return 0;
}