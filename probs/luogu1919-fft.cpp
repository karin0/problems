#include <cstdio>
#include <cmath>
#include <complex>

const int N = 333333;
const double pi = acos(-1.0);
typedef std::complex<double> comp;
comp _w[N], _winv[N];
void init(int n) {
    for (int i = 0; i < n; ++i) {
        _w[i] = comp(cos(2 * pi / n * i), sin(2 * pi / n * i));
        _winv[i] = std::conj(_w[i]);
    }
}
void trans(comp a[], int n, comp w[]) {
    static int i, j, k, l, m, t;
    static comp x;
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
        for (comp *p = a; p != a + n; p += l) {
            for (i = 0; i < m; ++i) {
                x = w[n / l * i] * p[m + i];
                p[m + i] = p[i] - x;
                p[i] += x;
            }
        }
    }
    // a^k = p * m + k (mod m)
}
void dft(comp a[], int n) {
    trans(a, n, _w);
}
void idft(comp a[], int n) {
    trans(a, n, _winv);
    for (int i = 0; i < n; ++i)
        a[i] /= n;
}
void mul(comp a[], comp b[], int n, int m) {
    static int i, l;
    for (l = 1; l < n + m; l <<= 1);
    init(l); // **
    dft(a, l);
    dft(b, l);
    for (i = 0; i < l; ++i)
        a[i] *= b[i];
    idft(a, l);
}
int main() {
    static int i, n, res[N];
    static comp a[N], b[N];
    static char s[N];
    scanf("%d", &n);
    scanf("%s", s);
    for (i = 0; i < n; ++i)
        a[n - i - 1] = s[i] - '0';
    scanf("%s", s);
    for (i = 0; i < n; ++i)
        b[n - i - 1] = s[i] - '0';
    mul(a, b, n, n);
    n = n + n - 1;
    for (i = 0; i < n; ++i)
        res[i] = floor(a[i].real() + 0.5); // printf("%d ", res[i]);
    for (i = 0; ; ++i) {
        if (res[i] >= 10)
            res[i + 1] += res[i] / 10, res[i] %= 10;
        else if (res[i] == 0 && i >= n) {
            for (n = i - 1; res[n] == 0; --n);
            break;
        }
    }
    for (i = n; i >= 0; --i)
        putchar(res[i] + '0');
    putchar('\n');
    return 0;
}
