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

int d[] = {1, 5, 10, 20, 50, 100, 200, 500, 1000, 2000};
int a[2333], use[2333], p;
bool ff() {
    re (i, 0, 10)
        use[d[i]] = 0;
    if (!p)
        return true;
    int tp = p;
    per (i, 9, 0) if (d[i] != 20 && d[i] != 200) {
        int &u = use[d[i]];
        u = std::min(a[d[i]], tp / d[i]);
        tp -= u * d[i];
        if (!tp)
            return true;
        ccc(tp, u, i, d[i]);
    }
    return false;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &p);
        re (i, 0, 10)
            scanf("%d", &a[d[i]]);
        int t = a[20] / 5;
        a[100] += t;
        a[20] -= t * 5;
        t = a[200] / 5;
        a[1000] += t;
        a[200] -= t * 5;
        bool ok = false;
        rep (i, 0, a[20]) {
            p -= i * 20;
            use[20] = i;
            if (p < 0)
                continue;
            rep (j, 0, a[200]) {
                p -= j * 200;
                use[200] = j;
                if (p < 0)
                    continue;
                if (!p || ff()) {
                    ok = true;
                    break;
                }
                p += j * 200;
            }
            if (ok)
                break;
            p += i * 20;
        }
        if (ok) {
            re (i, 0, 10) {
                ccc(i, d[i], use[d[i]], a[d[i]], "befor");
            }
            per (i, 9, 0) if (use[d[i]]) {
                re (j, 0, i) if (a[d[j]] - use[d[j]]) {
                    if ((d[j] == 20 && d[i] == 50) || (d[j] == 200 && d[i] == 500)) {
                        int un = std::min(a[d[j]] - use[d[j]], d[i] * use[d[i]] / d[j]);
                        un = un / 5 * 5;
                        ccf("use %d %d-s to save %d %d-s !!!\n", un, d[j], un*d[j]/d[i], d[i]);
                        use[d[j]] += un;
                        use[d[i]] -= un * d[j] / d[i];
                    } else {
                        int qe = d[i] / d[j];
                        int un = qe * use[d[i]];
                        int lft = a[d[j]] - use[d[j]]; // d[i] * use[d[i]] / d[j]);
                        if (un <= lft) {
                            ccf("use %d %d-s to save %d %d-s ???\n", un, d[j], use[d[i]], d[i]);
                            use[d[j]] += un;
                            use[d[i]] = 0;
                        } else {
                            int qe = d[i] / d[j];
                            un = lft / qe * qe;
                            use[d[j]] += un;
                            use[d[i]] -= un * d[j] / d[i];
                            ccf("use %d %d-s to save %d %d-s ...\n", un, d[j], un*d[j]/d[i], d[i]);
                        }
                    }
                }
            }
            int ans = 0;
            re (i, 0, 10) {
                ans += use[d[i]];
                ccc(i, d[i], use[d[i]], a[d[i]]-use[d[i]]);
            }
            printf("%d\n", ans);
        } else
            puts("-1");
    }
}