#include <akari>

IO<100, 100> io;

cint N = 1000002;

int mo;
struct Mat {
    int a[2][2];
    Mat operator * (const Mat &rhs) const {
        Mat r;
        re (i, 0, 2) re (j, 0, 2)
            r.a[i][j] = ((ll)a[i][0] * rhs.a[0][j] + (ll)a[i][1] * rhs.a[1][j]) % mo;
        return r;
    }
} I;
Mat pow(Mat a, int n) {
    Mat r = I;
    for (; n; n >>= 1, a = a * a)
        if (n & 1)
            r = r * a;
    return r;
}

char s[N];
int main() {
    I.a[0][0] = I.a[1][1] = 1;
    Mat a;
    a.a[0][0] = 0;
    a.a[0][1] = 1;
    ll x0, x1;
    io >> x0 >> x1 >> a.a[1][1] >> a.a[1][0] >> s >> mo;
    char *p = s;
    while (*p) ++p;

    Mat r = I;
    int t;
    for (--p; p >= s; --p, a = pow(a, 10))
        if (t = *p - '0')
            r = r * pow(a, t);
    
    io << ((ll)x0 * r.a[0][0] + (ll)x1 * r.a[0][1]) % mo daze;

    return 0;
}
    