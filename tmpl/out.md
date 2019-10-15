[TOC]

## 定义
```c++
#include <iostream>

#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define re(i_, s_, t_) for (int i_ = (s_); i_ < (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)
#define pe(i_, s_, t_) for (int i_ = (s_); i_ > (t_); --i_)

#ifdef AKARI
void cca() {
    std::cerr << std::endl;
}
template <typename T, typename... Args>
void cca(T a, Args... args) {
    std::cerr << a << ", ";
    cca(args...);
}
    #define ccc(args...) std::cerr << #args << "  =  ", cca(args)
#else
    #define ccc(...) 0
#endif

typedef long long ll;
```

## Miller–Rabin
```cpp
inline ll qmul(ll x, ll y, ll m) {
    ll tmp = x * y - ((ll)((long double)x / m * y + 0.5)) * m;
    return tmp < 0 ? tmp + m : tmp;
}

inline ll qpow(ll x, ll n, ll m) {
    ll r = 1;
    for (; n; n >>= 1, x = qmul(x, x, m))
        if (n & 1)
            r = qmul(r, x, m);
    return r;
}

const int pris[10] = { 3, 5, 7, 11, 13, 17, 19, 23 }, pris_n = 8;

inline bool is_prime(ll n) {
    if (n == 2)
        return true;
    if (n == 1 || !(n & 1))
        return false;
    ll t = n - 1;
    int k = 0;
    while (!(t & 1))
        t >>= 1, ++k;
    re (i, 0, pris_n) {
        if (n == pris[i])
            return true;
        ll x = qpow(pris[i], t, n), y = x;
        rep (j, 1, k) {
            x = qmul(x, x, n);
            if (x == 1 && !(y == 1 || y == n - 1))
                return false;
            y = x;
        }
        if (x != 1)
            return false;
    }
    return true;
}
```

## 欧拉函数 
```cpp
int phi(int n) {
    int t = sqrt(n) + 0.5;
    int ans = n;
    for (int i = 2; i <= t; i++)
        if (n % i == 0) {
            ans -= ans / i;
            do
                n /= i;
            while (n % i == 0);
        }
    if (n > 1)
        return ans - ans / n;
    return ans;
}
```

## 扩展欧拉定理 

若 $\gcd(a, m) = 1$ ，则 $a^{\varphi(m)} \equiv 1 \pmod{m}$ 。
$$
a^b\equiv
\begin{cases} 
a^{b\bmod\varphi(p)}&\gcd(a,p)=1 \\
a^b&\gcd(a,p)\ne1,b<\varphi(p)\\ a^{b\bmod\varphi(p)+\varphi(p)}&\gcd(a,p)\ne1,b\ge\varphi(p)
\end{cases} \pmod p
$$

## 欧拉筛求积性函数
```cpp
bool np[N];
int pri[N], mu[N], phi[N], d[N], z[N], pcnt;
ll f[N], g[N];
// d: 约数个数，z：最小质因子的次数，f：约数和，g：最小质因子的各幂次和
void sieve() {
    const int n = 10000000;
    np[0] = np[1] = true;
    mu[1] = phi[1] = d[1] = f[1] = g[1] = 1;
    rep (i, 2, n) {
        if (!np[i]) {
            pri[++pcnt] = i;
            mu[i] = -1;
            phi[i] = i - 1;
            d[i] = 2;
            z[i] = 1;
            f[i] = g[i] = i + 1;
        }
        ll v;
        for (int j = 1; j <= pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0) {
                mu[v] = 0;
                phi[v] = phi[i] * phi[j];
                z[v] = z[i] + 1;
                d[v] = d[i] / z[v] * (z[v] + 1);
                g[v] = g[i] * pri[j] + 1;
                f[v] = f[i] / g[i] * g[v];
                break;
            }
            mu[v] = -mu[i];
            phi[v] = phi[i] * (pri[j] - 1);
            z[v] = 1;
            d[v] = d[i] << 1;
            f[v] = f[i] * f[pri[j]];
            g[v] = pri[j] + 1;
        }
    }
    /* 前缀和
    rep (i, 2, n)
        mu[i] += mu[i - 1];
    */
}
```

## 线性求逆元

```cpp
inv[1] = 1;
rep (i, 2, n)
    inv[i] = ll(p - p / i) * inv[p % i] % p;
```

## exgcd
求 $ax + by = \gcd(a, b)$ 的一组整数解。

$a, b$ 中有负数时不能直接套用。

通解：
$$
\begin{cases} x = x_0 + \frac b {\gcd(a, b)} \cdot t \\ y=y_0-\frac a {\gcd(a, b)} \cdot t\end{cases}
$$
```c++
ll g;
void exgcd(ll a, ll b, ll &x, ll &y) {
    if (b) {
        exgcd(b, a % b, y, x);
        y -= x * (a / b);
    } else
        g = a, x = 1, y = 0;
}
```

## CRT

$x \equiv a_i \pmod{n_i}$ （$n_i$ 两两互质）的通解是 $x \equiv \sum a_i m_i m_i^{-1} \pmod n$，其中 $n = \prod n_i$， $m_i=\frac {n}{n_i}$，$m_i^{-1}$ 是 $m_i$ 在模 $n_i$ 意义下的逆元。

## 扩展 CRT

```python
import sys

g = x = y = 0
def exgcd(a, b):
    global g, x, y
    if b:
        exgcd(b, a % b)
        x, y = y, x
        y -= x * (a // b)
    else:
        g = a
        x = 1
        y = 0

k = int(input())
c1 = a1 = map(int, input().split())
for i in range(k - 1):
    c2, a2 = map(int, input().split())
    exgcd(c1, c2)
    t = a2 - a1
    if t < 0:
        t = -t
        x = -x
    tt = t // g
    if tt * g != t:
        print('No solution.')
        sys.exit(0)
    c3 = c1 // g * c2
    a1 = (a1 + x * tt * c1) % c3
    if a1 < 0:
        a1 += c3
    c1 = c3

print(a1)
```

## 线性基

```cpp
const int w = 50;
namespace basis {
    ll b[w + 1];
    void insert(ll x) {
        per (i, w, 0) {
            if (!x)
                return;
            if (!((x >> i) & 1))
                continue;
            if (b[i])
                x ^= b[i];
            else {
                re (j, 0, i)
                    if ((x >> j) & 1)
                        x ^= b[j];
                rep (j, i + 1, w)
                    if ((b[j] >> i) & 1)
                        b[j] ^= x;
                b[i] = x;
                return;
            }
        }
    }
    ll query() { // 最大异或和
        ll r = 0;
        rep (i, 0, w)
            r ^= b[i];
        return r;
    }
    ll c[w + 1];
    int cnt;
    void init() { // 初始化 k 大异或和
        rep (i, 0, w) if (b[i])
            c[cnt++] = b[i];
    }
    ll kth(ll k) { // k 大异或和
        if (n > cnt) { // n 是数的总数
            if (k == 1)
                return 0;
            --k;
        }
        ll r = 0;
        if (k >= (1ll << cnt))
            return -1; // 无解
        re (i, 0, cnt) if ((k >> i) & 1)
            r ^= c[i];
        return r;
    }
}
```

## 杜教筛（$\mu$, $\varphi$ 前缀和）
```c++
#include <map>

typedef long long ll;
typedef std::pair<int, ll> pil;

const int K = 1700000, N = K + 2;
bool np[N];
int pri[N], mu[N], pcnt;
ll phi[N];

inline void sieve() { // 最先调用
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
    rep (i, 2, n) {
        mu[i] += mu[i - 1];
        phi[i] += phi[i - 1];
    }
}

std::map<int, pil> s;
inline pil calc(ll n) {
    if (n <= K)
        return std::make_pair(mu[n], phi[n]);
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

## 二次剩余（**模奇素数**）
```c++
#include <cstdlib>
#include <ctime>
typedef long long ll;

int p, w; // 模数须为奇素数
struct S {
    int x, y;
    S(int x, int y) : x(x), y(y) {}
    S operator * (const S &r) const {
        return S(
            ((ll)x * r.x + (ll)y * r.y % p * w) % p,
            ((ll)x * r.y + (ll)y * r.x) % p
        );
    }
};

inline int qpow(ll a, int n) {
    ll r = 1;
    for (; n; n >>= 1, a = a * a % p)
        if (n & 1)
            r = r * a % p;
    return r;
}

inline int qpow(S a, int n) {
    S r = S(1, 0);
    for (; n; n >>= 1, a = a * a)
        if (n & 1)
            r = r * a;
    return r.x;
}

inline int solve(int n) { // 求出一个解 x，另一解为 p-x；返回 -1 表示无解
    n %= p;
    int t = p >> 1;
    if (qpow(n, t) == p - 1)
        return -1;
    while (true) {
        int a = rand() % p;
        w = ((ll)a * a % p - n) % p;
        if (w < 0)
            w += p;
        if (qpow(w, t) == p - 1)
            return qpow(S(a, 1), t + 1);
    }
}
// srand(time(0));
```

## 魔法快速乘
```c++
ll qmul(ll a, ll b) {
	return (a * b - (ll)((long double)a / mo * b + 1e-5) * mo + mo) % mo;
}
```

## 高斯消元
```c++
#include <cmath>
#include <algorithm>

const double eps = 1e-8;
double a[N][N]; // a[0 .. n-1][0 .. n]
bool gauss(int n) {
    re (i, 1, n) {
        int p = i;
        re (j, i + 1, n)
            if (fabs(a[j][i]) > fabs(a[p][i]))
                p = j;
        if (fabs(a[p][i]) < eps)
            return false;
        if (p != i)
            rep (j, i, n)
                std::swap(a[i][j], a[p][j]);
        re (j, 0, n)
            if (i != j) {
                double t = a[j][i] / a[i][i];
                per (k, n, i)
                    a[j][k] -= a[i][k] * t;
            }
    }
    return true;
}
// ans[i] = a[i][n] / a[i][i]
```
## 置换群

### 群

群是由集合 $G$ 和定义在 $G$ 上的二元运算 $*$ 构成的满足群公理的二元组 $(G,*)$.

群公理：
- 封闭性：$\forall a,b\in G, a*b\in G$
- 结合性：$\forall a,b,c \in G,(a*b)*c=a*(b*c)$
- 单位元：$\exists e\in G, \forall a\in G,a*e=e*a=a$
- 逆元：$\forall a\in G,\exists b\in G, a*b=e$ （$e$ 是单位元）

### Burnside 引理

设 $c(\pi)$ 为 $X$ 上的置换 $\pi$ 的不动点数（在置换 $\pi$ 下不变的染色数），则 $X$ 上的置换群 $G$ 的染色等价类数为 $\frac 1{|G|}\sum_{\pi \in G}c(\pi)$ .

### Polya 定理

设 $k(\pi)$ 为 $X$ 上的置换 $\pi$ 的循环节数，则 $X$ 上的置换群 $G$ 染 $m$ 种颜色的等价类数为 $\frac 1{|G|}\sum_{\pi \in G}m^{k(\pi)}$ .

这是 Burnside 定理的一个推论，此时 $c(\pi) = m^{k(\pi)}$.

### 环染色

给长 $n$ 的环染色，每个位置可以染 $m$ 种颜色，求旋转等价意义下不同的方案数：

$$
\frac{1}{n}\sum_{i=0}^{n-1} m^{\gcd(n,i)}
$$