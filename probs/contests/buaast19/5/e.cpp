#include <cstdio>
#include <algorithm>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
typedef unsigned long long ll;

const int N = 100002;

int fa[N], siz[N];
int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);    
}

ll f1, f2, f3, f4;
inline void del(int x) {
    // printf("Del %d, ", x);
    //    printf("f1 = %lld, f2 = %lld, f3 = %lld, f4 = %lld\n", f1,f2,f3,f4);
    f1 -= x;
    f2 -= x * f1;
    f3 -= x * f2;
    f4 -= x * f3;
}
inline void ins(int x) {
    // printf("Ins %d, ", x);
    //    printf("f1 = %lld, f2 = %lld, f3 = %lld, f4 = %lld\n", f1,f2,f3,f4);
    f4 += x * f3;
    f3 += x * f2;
    f2 += x * f1;
    f1 += x;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    f1 = n, f2 = (ll)n * (n - 1) >> 1, 
        f3 = f2 * (n - 2) / 3,
        f4 = f3 * (n - 3) >> 2;
    rep (i, 1, n)
        fa[i] = i, siz[i] = 1;
    printf("%lld\n", f4);
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        x = find(x);
        y = find(y);
        if (x != y) {
            del(siz[x]);
            del(siz[y]);
            ins(siz[x] += siz[y]);
            fa[y] = x;
        }
        printf("%lld\n", f4);
    }

}