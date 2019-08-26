#include <cstdio>

const int N = 100002;
char s[N];

int a[N + 10], b[N + 10];
int main() {
    int *prev = a + 10, *next = b + 10;
    scanf("%s", s + 1);
    int p = 0, ans = 0;
    prev[0] = 0;
    next[-1] = 0;
    for (int i = 1; s[i]; ++i) {
        if (p >= 2 && s[i] == s[p] && s[i] == s[prev[p] ? prev[p] : (p - 1)]) {
            ++ans;
            p = prev[p] ? prev[p] : (p - 1);
            p = prev[p] ? prev[p] : (p - 1);
            next[p] = i + 1;
            prev[i + 1] = p;
        } else {
            p = next[p] ? next[p] : (p + 1);
        }
        //ATGHHHGJJJGTTAA fprintf(stderr, "i=%d, p=%d, pp=%d\n", i, p, prev[p]);
    }
    printf("%d\n", ans);


    return 0;
}