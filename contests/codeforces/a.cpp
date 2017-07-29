#include <iostream>

long long n, k;
int main() {
    std::cin >> n >> k;
    std::cout << (((n / k) & 1) ? "YES\n" : "NO\n");

    return 0;
}
