#include <cstdio>

struct C {
    int x;
    C(int _x) : x(_x) {}
    void show() {
        puts("233");
    }
} *d;
int main() {
    C *c = new C(233);
    c->show();
    d = NULL;
    d->show();
    return 0;
}
