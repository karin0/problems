#include <cstdio>
#include <cstdlib>
#include <iostream>
using namespace std;

int main(){
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int e=c-a, f=d-b;
    if (f<0) {
        e--;
        f=60-b+d;
    }
    printf("%d %d", e, f);
    return 0;
}