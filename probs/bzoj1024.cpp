/*



*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

double ans=2147483600, s0;

int gcd(int a, int b) {
    return b ? gcd(b, a%b) : a;
}

double dfs(int x, int y, int t, double rmax) { // t for times left
    if (t==0) {
        ans=min(ans, rmax);
        return 1.0;
    }
    if (x<y) swap(x, y);
    if (y==0) return 1.0;
    for (int i=0; i<2; ++i) {
        int amin=floor(s0/y);
        for (int a=amin; a<=x; ++a) {
            rmax=max(max(rmax, dfs(a, y, t-1)), dfs(x-a, y, t-1))
        } 

        swap(x, y);
    }
    return rmax;
}

int x, y, n, g;
int main() {
    scanf("%d%d%d", &x, &y, &n);
    g=gcd(x, y);
    x/=g;
    y/=g;
    s0=x*y/ ((double)n);
    dfs(x, y, n-1, 1.0);
    printf("%d\n", ans);
    return 0;
}
