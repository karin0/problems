#include <iostream>
#include <cstring>
using namespace std;

int main(){
    int n;
    cin >> n;
    int s[n+10][n+10];
    memset(s, 0, sizeof(s));
    s[1][n/2+1]=1;
    int px=1, py=n/2+1, nx, ny;
    for (int k=2; k<=n*n; k++) {
        if (px==1) {
            if (py!=n) {
                nx=n; ny=py+1;
            } else {
                nx=px+1; ny=py;
            }
        } else
        if (py==n) {
            nx=px-1; ny=1;
        } else {
            if (s[px-1][py+1]==0) {
                nx=px-1; ny=py+1;
            } else {
                nx=px+1; ny=py;
            }
        }
        //if (s[nx][ny]!=0) cout << "Fu"<<s[nx][ny] <<"ck"<<k<<"You";
        s[nx][ny]=k;
        px=nx; py=ny;
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            cout << s[i][j];
            if (j!=n) cout << ' ';
        }
        if (i!=n) cout << endl;
    }
    return 0;
}