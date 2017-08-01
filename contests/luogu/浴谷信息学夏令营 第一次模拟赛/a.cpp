#include <cstdio>
#include <algorithm>
/*
6 4 = 2
4 2 = 2
2 2 = 0

8 4 = 4
4 4 = 0

16 8 = 8
8 8 = 0

3 2 = 1
2 1 = 1
1 1 = 0

7 4 = 3
4 3 = 1
3 1 = 2
2 1 = 1
1 1 = 0

9 7 = 2
7 2 = 5
5 2 = 3
3 2 = 3
2 1 = 1
1 1

*/
int main() {
    long long n, m, g, cnt = 1;
    scanf("%lld%lld", &n, &m);
    while (n - m) {
        if (n < m)
            std::swap(n, m);
        g = n - m;
        ++cnt;
        if (m > g) {
            n = m;
            m = g;
        } else {
            n = g;
        }
    }
    printf("%lld\n", cnt);
    return 0;
}
