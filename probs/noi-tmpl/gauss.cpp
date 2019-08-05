#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;

const int N = 503;
const double eps = 1e-8;
double a[N][N];

bool gauss(const int n) {
    re (i, 0, n) {
        int p = i;
        re (j, i + 1, n) if (fabs(a[j][i]) > fabs(a[p][i]))
            p = i;
        if (fabs(a[p][i]) < eps)
            return false;
        if (p != i) rep (j, i, n)
            std::swap(a[i][j], a[p][j]);
        re (j, 0, n) if (i != j) {
            double t = a[j][i] / a[i][i];
            per (k, n, i)
                a[j][k] -= a[i][k] * t;
        }
    }
    return true;
}
