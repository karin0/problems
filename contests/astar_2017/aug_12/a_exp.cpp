#include <cstdio>
#include <stack>

int p, b;

int main() {
    p = 1000;
    for (b = 1; b <= 1000000000; ++b) {
        bool flag = true;
        for (int k = 1; k <= 10000; ++k) {
            int x = k * b;
            int res = 0;
            while (x)
                res += x % p, x /= p;
            if (res % b) {
                // printf("%d have failed at %d, %d\n", b, k, k * b);
                flag = false;
                break;
            }
        }
        if (flag) {
            int bb = b;
            std::stack<int> sta;
            while (bb)
                sta.push(bb % p), bb /= p;
            printf("%d is good, aka ", b);
            while (!sta.empty()) {
                printf("%d ", sta.top());
                sta.pop();
            }
            printf("%d\n");
        }
    }

    return 0;
}
