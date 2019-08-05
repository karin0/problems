#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 333333; // O(n + m) -> 2^k
const double pi = acos(-1.0);
// typedef std::complex<double> comp;
struct comp {
    double re, im;
    comp() {}
    comp(double _r, double _i) : re(_r), im(_i) {}
    comp operator + (const comp &b) const {
        return comp(re + b.re, im + b.im);
    }
    comp &operator += (const comp &b) {
        return *this = *this + b;
    }
    comp operator - (const comp &b) const {
        return comp(re - b.re, im - b.im);
    }
    comp operator * (const comp &b) const {
        return comp(re * b.re - im * b.im, re * b.im + im * b.re);
    }
    comp &operator *= (const comp &b) {
        return *this = *this * b;
    }
    template <class T>
    comp &operator = (const T &b) {
        return *this = comp(b, 0);
    }
    comp conj() const {
        return comp(re, -im);
    }
} w[N], winv[N];
int rev[N];
int init(const int n, const int m) {
    static int l, k;
    for (k = 0, l = 1; l < n + m; l <<= 1, ++k);
    for (int i = 0; i < l; ++i) {
        w[i] = comp(cos(2 * pi / l * i), sin(2 * pi / l * i));
        winv[i] = w[i].conj();
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
    }
    return l;
}
void dft(comp *a, const int n) {
    int i, l, m, t;
    for (i = 0; i < n; ++i)
        if (i < rev[i])
            std::swap(a[i], a[rev[i]]);
    for (l = 2; l <= n; l <<= 1) {
        m = l >> 1;
        t = n / l;
        for (comp *p = a; p != a + n; p += l)
            for (i = 0; i < m; ++i) {
                comp x = w[t * i] * p[m + i];
                p[m + i] = p[i] - x;
                p[i] += x;
            }
    }
}
void idft(comp *a, const int n) {
    std::swap(w, winv);
    dft(a, n);
    std::swap(w, winv);
    for (int i = 0; i < n; ++i)
        a[i].re /= n;
}
void mul(comp *a, comp *b, const int l) {
    static int i;
    dft(a, l);
    dft(b, l);
    for (i = 0; i < l; ++i)
        a[i] *= b[i];
    idft(a, l);
}

int main() {
    static int i, n, l;
    static double ans[N], f[N], g[N];
    static comp c1[N], c2[N];
    scanf("%d", &n);
    l = init(n, n);
    for (i = 0; i < n; ++i)
        scanf("%lf", &f[i]), c1[i] = f[i];
    for (i = 1; i < n; ++i)
        c2[i] = g[i] = (double)1.0 / ((long long)i * i);
    mul(c1, c2, l);
    for (i = 0; i < n; ++i)
        ans[i] = c1[i].re, c1[i] = f[n - i - 1], c2[i] = g[i];
    for (i = n; i < l; ++i)
        c1[i] = c2[i] = 0;
    mul(c1, c2, l);
    for (i = 0; i < n; ++i)
        printf("%.3lf\n", ans[i] - c1[n - i - 1].re);
    return 0;
}
