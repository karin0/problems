#include <stdio.h>

#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define AKARI

const int w = 10;
int b[13];
void insert(int x) {
    per (i, w, 0) {
        if (!x)
            return;
        if (!((x >> i) & 1))
            continue;
        if (b[i])
            x ^= b[i];
        else {
            re (j, 0, i)
                if ((x >> j) & 1)
                    x ^= b[j];
            rep (j, i + 1, w)
                if ((b[j] >> i) & 1)
                    b[j] ^= x;
            b[i] = x;
            return;
        }
    }
}
int calc() {
    int res = 0;
    rep (i, 0, w)
        res ^= b[i];
    return res;
}
int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int x;
        scanf("%d", &x);
        insert(x);
    }
    printf("%d\n", calc());

    return 0;
}
