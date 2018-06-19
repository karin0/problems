#include <cstdio>
#include <algorithm>
#define MAXN 20001
#define LEAST -2147483640
using std::lower_bound;
int st_val[MAXN], st_ind[MAXN];
int mod, top = 0; // sta[1.. ..]
int cnt = 0;
void insert(int x) {
    x = -x;
    int pos = lower_bound(st_val + 1, st_val + top + 1, x) - st_val;
    st_val[pos] = x;
    st_ind[pos] = ++cnt;
    top = pos;
}
int query(int l) {
    return -(st_val[lower_bound(st_ind + 1, st_ind + top + 1, cnt - l + 1) - st_ind]);
}
int main() {
    int q;
    scanf("%d%d", &q, &mod);
    char oper[3];
    int t, mem = 0;
    std::fill(st_val, st_val + q, LEAST);
    while (q--) {
        scanf("%s%d", oper, &t);
        if (oper[0] == 'A') { // append
            insert((t + mem) % mod);    
        } else { // query
            printf("%d\n", mem = query(t));
        }
    }

    return 0;
}
