#include <cstdio>

typedef long long ll;
const int n = 1000000;
int pri[n], pcnt;
bool np[n];
void sieve() {
    static int i, j;
    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i;
        for ()
    }
}

int main() {
    sieve(1000000);
    while (true) {
        scanf("%d", &n);
        if (n == 0)
            return 0;
        sieve(n);
    }
    return 0;
}
