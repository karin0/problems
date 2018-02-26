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
    template <class T>
    comp operator * (const T &b) const {
        return comp(re * b, im * b);
    }
    template <class T>
    comp operator / (const T &b) {
        return comp(re / b, im / b);
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
int init(const int n) {
    static int l, k;
    for (k = 0, l = 1; l < n; l <<= 1, ++k);
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

int main() {
    static int i, n, m, l, x;
    static comp a[N], b[N], c[N];
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &x);
        a[x].re += 1;
        b[x * 2].re += 1;
        c[x * 3].re += 1;
        m = std::max(m, x);
    }
    l = init(m *= 3);
    dft(a, l);
    dft(b, l);
    dft(c, l);
    for (i = 0; i < l; ++i)
        a[i] = (a[i] * a[i] * a[i] - a[i] * b[i] * 3 + c[i] * 2) / 6.0
             + (a[i] * a[i] - b[i]) / 2.0 
             +  a[i];
    idft(a, l);
    for (i = 0; i <= m; ++i) {
        x = floor(a[i].re + 0.5);
        if (x)
            printf("%d %d\n", i, x);
    }

    return 0;
}
