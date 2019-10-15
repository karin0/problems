#include <akari>
#include <map>

typedef long long ll;
typedef std::pair<int, ll> pil;

const int K = 1700000, N = K + 2;
bool np[N];
int pri[N], mu[N], pcnt;
pil rec[N];
ll phi[N];

inline void sieve() {
    const int n = K;
    np[0] = np[1] = true;
    mu[1] = phi[1] = 1;
    rep (i, 2, n) {
        if (!np[i]) {
            pri[++pcnt] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }
        ll v;
        for (int j = 1; j <= pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0) {
                mu[v] = 0;
                phi[v] = phi[i] * pri[j];
                break;
            }
            mu[v] = -mu[i];
            phi[v] = phi[i] * (pri[j] - 1);
        }
    }
    rec[1] = std::make_pair(1, 1);
    rep (i, 2, n)
        rec[i] = std::make_pair(mu[i] += mu[i - 1], phi[i] += phi[i - 1]);
}

std::map<int, pil> s;
inline pil calc(ll n) {
    if (n <= K)
        return rec[n];
    std::map<int, pil>::iterator it = s.find(n);
    if (it != s.end())
        return it->second;
    int smu = 1;
    ll sphi = n * ll(n + 1) / 2;
    for (ll ni, i = 2; i <= n; i = ni + 1) {
        ll r = n / i;
        ni = n / r;
        pil t = calc(r);
        r = ni - i + 1;
        smu -= r * t.first;
        sphi -= r * t.second;
    }
    return s[n] = std::make_pair(smu, sphi);
}

io_t io;

int main() {
    sieve();
    int T;
    io >> T;
    while (T--) {
        int n;
        io >> n;
        // ccc(n);
        pil x = calc(n);
        io << x.second << ' ' << x.first << '\n';
    }
}
