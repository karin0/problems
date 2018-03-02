#include <cstdio>
#include <cmath>

const int MAXN = 10000005, MAXM = 100005;

int n = 1;
int pri[MAXN], pcnt, f[MAXN];
bool notp[MAXN], iss[MAXN];
inline void shaker() {
    static int i, j;
    static long long v;
    notp[0] = notp[1] = true;
    for (i = 2; i <= n; ++i) {
        if (!notp[i])
            pri[++pcnt] = i;
        for (j = 1; j <= pcnt; ++j) {
            v = (long long)i * (long long)pri[j];
            if (v > n)
                break;
            notp[v] = true;
            if (i % pri[j] == 0) {
                // if (!notp[i / pri[j]])
                //    iss[i] = true, printf("%d fucks %d\n", i, pri[j]);
                break;
            }
        }
    }
    for (i = 2; i <= n; ++i) {
        for (j = 1; j <= pcnt; ++j) {
            if (i % pri[j] == 0 || pri[j] > i) {
                if (!notp[i / pri[j]])
                    iss[i] = true, printf("%d fucks %d\n", i, pri[j]);
                break;
            }
        }
    }
}


int main() {
    int i, j, m, l, r;
    n = 100;
    shaker();
    for (i = 1; i <= n; ++i) {
        printf("%d: %d\n", i, iss[i]);
    }
        

    return 0;
}
