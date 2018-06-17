/*
Tyvj 1001

排序，素数判定
*/
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int n, k, m, a[10100];
bool notprime;
int main() {
    scanf("%d%d", &n, &k);
    for (int i=0; i<n; i++) scanf("%d", a+i);
    sort(a, a+n);
    m = a[n-k] - a[k-1];
    if (m<2 || (m!=2&&m%2==0)) {
        notprime = true;
    } else for (int i=3; i<(int)(sqrt(m)+1); i+=2)
        if (m%i==0) {
            notprime = true;
            break;
        }
    printf(notprime ? "NO" : "YES");
    printf("\n%d\n", m);

    return 0;
}
