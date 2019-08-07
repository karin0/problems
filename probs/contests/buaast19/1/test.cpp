#include <iostream>
#include <algorithm>

int main() {
    int a = 0, b = 1;
    int &x = a, &y = b;
    std::swap(x, y);
    x = 10;
    std::cout << a << std::endl << b << std::endl;
}