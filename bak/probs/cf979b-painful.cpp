#include <cstdio>
#include <cctype>
#include <algorithm>
#include <string>
#include <iostream>

int k;
int rd() {
    static std::string s;
    static int cnt[200], x;
    std::fill(cnt, cnt + 128, 0);
    std::cin >> s;
    x = 0;
    for (char c : s)
        x = std::max(x, ++cnt[c]);
    if (k != 1) // k could be 0 or 1(when the rule fails)
        return std::min((int)s.length(), x + k);
    if (x == s.length())
        return s.length() - 1;
    return x + 1;
}
std::pair<int, std::string> a[3];
int main() {
    std::cin >> k;
    a[0] = std::make_pair(rd(), "Kuro");
    a[1] = std::make_pair(rd(), "Shiro");
    a[2] = std::make_pair(rd(), "Katie");
    std::sort(a, a + 3);
    std::cout << ((a[2].first != a[1].first) ? a[2].second : "Draw") << std::endl;

    return 0;
}
