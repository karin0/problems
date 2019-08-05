#include <cstdio>

void foo(int x) {
    puts("Got int");
}
void foo(void *x) {
    puts("Got ptr");
}
int main() {
    foo((void *)NULL);

    return 0;
}
