#include <cstdio>
#include <cstring>
#include <vector>

const int MAXL = 110;

struct BigInt {
    std::vector<int> v;
    /*BigInt () {
        v.push_back(0);
    }*/
};
BigInt mul(const BigInt &x, const BigInt &y, int lim) {
    BigInt res;
    // res.v.resize(x.v.size() + y.v.size());
    res.v.resize(lim);
    int sx = x.v.size();
    int sy = y.v.size();
    for (int i = 0; i < sx; ++i) {
        for (int j = 0; j < sy; ++j) {
            if (i + j > lim - 1)
                break;
            res.v[i + j] += x.v[i] * y.v[j];
            res.v[i + j + 1] += res.v[i + j] / 10;
            res.v[i + j] %= 10;
        }
    }
    /*int s = res.v.size();
    while (s > 1 && res.v[s - 1] == 0)
        --s;
    res.v.resize(s);
    */
    res.v.resize(lim);
    return res;
}
bool operator == (const BigInt &x, const BigInt &y) {
    int sx = x.v.size();
    int sy = y.v.size();
    if (sx != sy)
        return false;
    for (int i = 0; i < sx; ++i)
        if (x.v[i] != y.v[i])
            return false;
    return true;
}

inline void pt(const BigInt &x) {
    printf("[");
    for (int i = (int)x.v.size() - 1; i >= 0; --i)
        printf("%d", x.v[i]);
    printf("]\n");
}

inline void qpow(const BigInt &x, int p, int siz, BigInt &res) {
    res = x;
    --p;
    BigInt b = x;
    for(; p; p >>= 1, b = b * b)
        if (p & 1)
            res = res * b;
}

int len, m;
char s[MAXL];
bool check[10];
BigInt a, x, unit;

int main() {
    int i, j, res, lres = 1, dig, ans = 1, cur;
    scanf("%s%d", s, &m);
    len = strlen(s);
    for (i = len - 1; i >= len - m; --i)
        a.v.push_back(s[i] - '0');
    unit.v.push_back(s[len - 1] - '0');
    // unit = a;
    for (i = 1; i <= m; ++i) { // 处理后 i 位
        x.v.push_back(s[len - i] - '0');
        dig = a.v[i - 1];
        
        // unit = x;
        // for (j = 1; j < ans; ++j)
        //    unit = unit * x;
        qpow(x, ans, i, unit);
        puts("XD1");
        unit.v.resize(i);
        puts("XD2");
        
        res = 0;
        memset(check, false, sizeof(check));
        while (true) {
            ++res;
            x = x * unit;
            x.v.resize(i);
            cur = x.v[i - 1];
            if (cur == dig)
                break;
            else if (check[cur]) {
                puts("-1");
                return 0;
            } else
                check[cur] = true;
        }
        pt(x);
        // printf("(%d, %d)\n", i, res);
        ans *= res;
    }
    
    printf("%d\n", ans);
    return 0;
}
