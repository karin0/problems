#include <cstdio>
#include <vector>
#include <cmath>
const int MAXL = 33;

std::vector<int> kth[MAXL]; // starts with 0
int nq[MAXL], lk[MAXL];

bool is_prime(int x) {
    // Assuming x % 2 == 1
    int ub = sqrt(x) + 1;
    for (int i = 3; i <= ub; i += 2)
        if (!(x % i))
            return false;
    return true;
}

int main() {
    int n, k, l, q, a, p2l;
    scanf("%d", &n);
    for (l = 11; l <= 33; ++l)
        nq[l] = 1, lk[l] = 0;
    while (n--) {
        scanf("%d%d", &l, &k);
        if (lk[l] < k) {
            p2l = 1 << l;
            q = nq[l];
            a = q * p2l + 1;
            do {
                if (is_prime(a)) {
                    kth[l].push_back(a);
                    ++lk[l];
                }
                ++q;
                a += p2l;
            } while (lk[l] < k);
            nq[l] = q;
        }
        printf("%d\n", kth[l][k - 1]);
    }
    return 0;
}
