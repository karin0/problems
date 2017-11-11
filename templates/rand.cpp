#include <cstdio>
#include <cstdlib>
#include <ctime>

int main() {
    static int t = 10, x;
    srand(time(0));
    while (t--) {
        x = rand();
        printf("%d\n", x);
    }

    return 0;
}
