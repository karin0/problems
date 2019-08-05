#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstring>
#include <algorithm>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

typedef long long ll;
ll k;
ll calc(std::string &s) {
    static ll i, cnt[100000], mc, mov;
    ll n = s.length();
    memset(cnt, 0ll, sizeof(cnt));
    mc = 0;
    for (i = 0; i < n; ++i) {
        char c = s[i];
        ++cnt[c];
        mc = std::max(mc, cnt[c]);
    }
    mov = n - mc;
    if (mov >= k)
        return mc + k;
    ll nk = (k - mov) % n;
    if (nk & 1)
        return std::max(n - 1, 1ll);
    return n;
}

std::string a, b, c;
ll h[3];
int main() {
    std::cin >> k >> a >> b >> c;
    h[0] = calc(a), h[1] = calc(b), h[2] = calc(c);
    ll q = std::max(h[0], std::max(h[1], h[2]));
    ll cnt = 0;
    for (ll i = 0; i < 3; ++i)
        if (h[i] == q)
            ++cnt;
    if (cnt > 1)
        puts("Draw");
    else {
        ll i;
        for (i = 0; h[i] != q; ++i);
        if (i == 0)
            puts("Kuro");
        else if (i == 1)
            puts("Shiro");
        else
            puts("Katie");
    }

    return 0;
}
