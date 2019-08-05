#include <akari>

IO<10, 10> io;

int main() {
    int v[4] = {0, 3, 1, 2};
    std::pair<char, int> a[3];
    int x = io;
    rep (i, 0, 2)
        a[i] = std::make_pair('D' - v[(x + i) % 4], i);
    const auto &e = *std::min_element(a, a + 3);
    io << e.second << ' ' << e.first daze;

    return 0;
}
