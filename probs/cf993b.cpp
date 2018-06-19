#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x)
    #define ccf(x)
    #define cccc(...)
#endif
typedef long long ll;
typedef std::pair<int, int> pii;
#define x first
#define y second
int n, m, okc;
pii a[15], b[15];
bool in(int x, pii pa) {
    return pa.x == x || pa.y == x;
}
int sam(pii pa, pii pb) {
    if (pa.x == pb.x)
        return pa.x;
    if (pa.x == pb.y)
        return pa.x;
    if (pa.y == pb.x)
        return pa.y;
    if (pa.y == pb.y)
        return pa.y;
    return 0;
}
int main() {
    static int i, j, k, aa;
    scanf("%d%d", &n, &m);
    rep (i, 1, n) {
        scanf("%d%d", &a[i].x, &a[i].y);
        if (a[i].x > a[i].y)
            std::swap(a[i].x, a[i].y); // *** or fst
    }
    rep (i, 1, m) {
        scanf("%d%d", &b[i].x, &b[i].y);
        if (b[i].x > b[i].y)
            std::swap(b[i].x, b[i].y); // ***
    }
    rep (k, 1, 9) {
        rep (i, 1, n) if (in(k, a[i])) {
            rep (j, 1, m) if (a[i] != b[j] && in(k, b[j])) {
                aa = k;
                // ccf(k);
                ++okc;
                if (okc > 1)
                    goto ex2;
                goto ex1;
            }
        }
ex1:
        2333;
    }
ex2:
    if (okc == 1)
        return printf("%d\n", aa), 0;
    rep (i, 1, n) {
        int fnd = 0;
        rep (j, 1, m) if (a[i] != b[j]) {
            int s = sam(a[i], b[j]);
            if (!s)
                continue;
            if (!fnd)
                fnd = s;
            else if (fnd != s)
                return puts("-1"), 0;
        }
    }
    rep (i, 1, m) {
        int fnd = 0;
        rep (j, 1, n) if (a[j] != b[i]) {
            int s = sam(a[j], b[i]);
            if (!s)
                continue;
            if (!fnd)
                fnd = s;
            else if (fnd != s)
                return puts("-1"), 0;
        }
    }
    puts("0");

    return 0;
}

