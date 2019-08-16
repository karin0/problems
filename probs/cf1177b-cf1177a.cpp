#include <akari>

IO<20, 20> io;

ll pow10[100];
int main() {
    ll k, sum = 0, ls;
    io >> k;

    pow10[0] = 1;
    int i = 0;
    do {
        ++i;
        pow10[i] = pow10[i - 1] * 10;
        ls = sum;
        sum += i * (pow10[i] - pow10[i - 1]);
        ccc(i, sum);
    } while (sum < k);
    k -= ls;
    ll t = k / i;
    int u = k - i * t;
    ll n = pow10[i - 1] - 1 + t;
    if (u) {
        ++n;
        int r = i - u;
        while (r--)
            n /= 10;
    }
    ccc(i, k, n, u, t);
    io << char('0' + n % 10) daze;
}
