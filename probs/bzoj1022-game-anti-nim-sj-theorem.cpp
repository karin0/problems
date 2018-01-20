#include <cstdio>

int main() {
    static int n, t, x, sg, p;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        p = sg = 0;
        while (n--) {
            scanf("%d", &x);
            sg ^= x;
            p |= x > 1;
        }
        puts((p ^ bool(sg)) ? "Brother" : "John");
    }

    return 0;
}
