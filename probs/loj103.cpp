#include <cstdio>
const int MAXS = 1e6 + 50;
const int MOD = 1e9 + 7;
const int BASE = 131;

char a[MAXS], b[MAXS];
int p; // = pow(BASE, r - l + 1) % MOD = pow(BASE, b_len) % MOD

struct Hash {
    int hash[MAXS], len;
    
    inline void init(char* s) {
        hash[0] = s[0]; // % MOD;
        int i;
        for (i = 1; s[i]; ++i) {
            hash[i] = ((long long)hash[i - 1] * BASE + s[i]) % MOD;
        }
        len = i;
    }
    inline int get_sub_hash(int l, int r) {
        return (hash[r] - ((long long)hash[l - 1] * p % MOD) + MOD) % MOD;
    }
} a_hash;

int main() {
    int b_hash, b_len, ans = 0;
    scanf("%s%s", a, b);
    a_hash.init(a);
    
    b_hash = 0;
    b_len = 0;
    char* c;
    p = 1;
    for (c = &b[0]; *c; ++c) {
        b_hash = ((long long)b_hash * BASE + *c) % MOD;
        p = ((long long)p * BASE) % MOD;
    }
    b_len = c - b;
    // p = qpow_mod(BASE, b_len);
    for (int i = 0; i <= a_hash.len - b_len; ++i) {
        if (a_hash.get_sub_hash(i, i + b_len - 1) == b_hash) {
            ++ans;
        }
    }
    printf("%d\n", ans);

    return 0;
}
