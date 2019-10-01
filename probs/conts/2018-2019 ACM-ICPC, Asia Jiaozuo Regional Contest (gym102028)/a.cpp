#include <akari>

IO<1000000, 1000000> io;

const char *s[] = {
    "Typically Otaku",
    "Eye-opener",
    "Young Traveller",
    "Excellent Traveller",
    "Contemporary Xu Xiake"
};

int main() {
    int T;
    io >> T;
    while (T--) {
        int a, b, c, d;
        io >> a >> b >> c >> d;
        io << s[bool(a) + bool(b) + bool(c) + bool(d)] << '\n';
    }
}