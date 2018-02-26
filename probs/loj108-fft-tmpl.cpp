#include <cstdio>
#include <cmath>
#include <algorithm>

const int N = 333333; // O(n + m) -> 2^k
const double pi = acos(-1.0);
//typedef std::complex<double> comp;
struct comp {
    double re, im;
    comp() {}
    comp(double _r, double _i) : re(_r), im(_i) {}
    comp operator + (const comp &b) const {
        return comp(re + b.re, im + b.im);
    }
    comp &operator += (const comp &b) {
        return (*this = *this + b);
    }
    comp operator - (const comp &b) const {
        return comp(re - b.re, im - b.im);
    }
    comp operator * (const comp &b) const {
        return comp(re * b.re - im * b.im, re * b.im + im * b.re);
    }
    comp &operator *= (const comp &b) {
        return (*this = *this * b);
    }
    comp operator / (const int &b) const {
        return comp(re / b, im / b);
    }
    comp &operator /= (const int &b) {
        return (*this = *this / b);
    }
    void operator = (const int b) {
        re = b, im = 0;
    }
    comp conj() const {
        return comp(re, -im);
    }
};

comp w[N], winv[N];
void init(const int n) {
    for (int i = 0; i < n; ++i) {
        w[i] = comp(cos(2 * pi / n * i), sin(2 * pi / n * i));
        winv[i] = w[i].conj();
    }
}
void dft(comp *a, const int n) {
    int i, j, k, t, l, m;
    for (k = 0; (1 << k) < n; ++k);
    for (i = 0; i < n; ++i) {
        t = 0;
        for (j = 0; j < k; ++j)
            if (i & (1 << j))
                t |= (1 << (k - j - 1));
        if (i < t)
            std::swap(a[i], a[t]);
    }
    for (l = 2; l <= n; l <<= 1) {
        m = l >> 1;
        for (comp *p = a; p != a + n; p += l)
            for (i = 0; i < m; ++i) {
                comp x = w[n / l * i] * p[m + i];
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
        a[i] /= n;
}
void mul(const int *a, const int *b, const int n, const int m, int *res) {
    static int i, l;
    static comp c1[N], c2[N];
    for (l = 1; l < n + m; l <<= 1);
    for (i = 0; i < n; ++i)
        c1[i] = a[i];
    for (i = 0; i < m; ++i)
        c2[i] = b[i];
    init(l);
    dft(c1, l);
    dft(c2, l);
    for (i = 0; i < l; ++i)
        c1[i] *= c2[i];
    idft(c1, l);
    for (i = 0; i < n + m - 1; ++i)
        res[i] = floor(c1[i].re + 0.5);
}

int main() {
    static int i, n, m, f[N], g[N], res[N];
    scanf("%d%d", &n, &m);
    ++n, ++m;
    for (i = 0; i < n; ++i)
        scanf("%d", &f[i]);
    for (i = 0; i < m; ++i)
        scanf("%d", &g[i]);
    mul(f, g, n, m, res);
    for (i = 0; i <= n + m - 2; ++i)
        printf("%d ", res[i]);

    return 0;
}
