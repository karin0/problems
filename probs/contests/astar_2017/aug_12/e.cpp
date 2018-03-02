#include <cstdio>


inline int days(long long year) {
    return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 > 0)) ? 366 : 365;
}

int y, m, d;

inline void work_1() { // 到下一年的这一天经过的天数是这一年的天数
    int diff = 0;
    do {
        diff = (diff + days(y)) % 7;
        y = y + 1;
    } while (diff);
    printf("%d\n", y);
}
inline void work_2() { // 到下一年的这一天经过的天数是下一年的天数
    int diff = 0;
    do {
        y = y + 1;
        diff = (diff + days(y)) % 7;
    } while (diff);
    printf("%d\n", y);
}
inline void work_spe() {
    int diff = 0;
    do {
        diff = (diff + days(y)) % 7;
        y = y + 1;
    } while (diff || days(y) == 365);
    printf("%d\n", y);
}
int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        scanf("%d%d%d", &y, &m, &d);
        m = -m, d = -d;
        if (m == 2 && d == 29)
            work_spe();
        else if (m > 2)
            work_2();
        else
            work_1();
    }

    return 0;
}
