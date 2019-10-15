typedef long long ll;

ll g;
void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b) {
        exgcd(b, a % b, y, x);
        y -= x * (a / b);
    } else
        g = a, x = 1, y = 0;
}
