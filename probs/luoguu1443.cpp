#include <cstdio>

int n, str;
int main() {
    int t;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &t);
        str += t;
    }
    if (str >= 100)
        if (str > 250)
            printf("cool\n");
        else
            printf("good\n");
    else
        if (str >= 30)
            printf("run!\n");
        else
            printf("oh,no!\n");

    return 0;
}
