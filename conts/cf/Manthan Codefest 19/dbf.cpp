#include <cstdio>
#include <algorithm>
#include <iostream>
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
typedef long long ll;
typedef const int cint;

#ifdef AKARI
void cca() {
    std::cerr << "\033[39;0m" << std::endl;
}
template <typename T, typename... Args>
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", cca(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_, s_, t_) rep(i, s_, t_)
#else
    #define ccc(...) 0
    #define ccf(...) 0
    #define crep(...) if (0)
#endif

int n;
ll s[100], ss[100], sp[100];

void ff(int *a) {
        printf(" p: ");
        rep (i, 1, n)
            printf("%d ", a[i]);
        printf("\nsp: ");
        rep (i, 1, n) {
            sp[i] = sp[i - 1] + a[i];
            printf("%lld ", sp[i]);
        }
        printf("\n s: ");
        rep (i, 1, n) {
            s[i] = 0;
            re (j, 1, i) if (a[j] < a[i])
                s[i] += a[j];
            printf("%lld ", s[i]);
        }
        printf("\nss: ");
        rep (i, 1, n) {
            ss[i] = ss[i - 1] + s[i];
            printf("%lld ", ss[i]);
        }
        printf("\nqa: ");
        rep (i, 1, n) {
            printf("%lld ", sp[i] - s[i]);
        }
        putchar('\n');
        putchar('\n');
}

int a[100], b[100];
int main() {
    scanf("%d", &n);
    rep (i, 1, n)
        a[i] = i;
    do {
        ff(a);
        rep (i, 1, n)
            b[a[i]] = i;
        puts("inv:");
        ff(b);
    } while (std::next_permutation(a + 1, a + n + 1));
    // QAQAQAQAQAQAQ..
    // QAQAQAQAQAQAQ..
    // QAQAQAQAQAQAQ..
    // QAQAQAQAQAQAQ..
}