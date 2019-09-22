#include <akari>
#include <cctype>

IO<1000000, 1000000> io;

cint N = 100002;

char a[20];
int tb[256];
int main() {
    tb['b'] = tb['c'] = 1;
    tb['i'] = tb['f'] = 4;
    tb['_'] = 16;
    tb['d'] = 8;

    int T;
    io >> T;
    rep (ks, 1, T) {
        int n, ans = 0;
        io >> n;
        while (n--) {
            io >> a;
            int siz = tb[a[0]];
            if (!siz) {
                io >> a;
                siz = a[0] == 'd' ? 16 : 8;
            }
            char c;
            while ((c = io.gc()) != ';') {
                if (c == '[') {
                    int t = 0;
                    c = io.gc();
                    do
                        t = t * 10 + c - '0';
                    while ((c = io.gc()) != ']');
                    ans += siz * t;
                    io.gc();
                    goto ex;
                }
            }
            ans += siz;
            ex: 233;
        }
        io << "Case #" << ks << ": " << (ans >> 10) + bool(ans & 1023) daze;
        // '#'!!!
    }
}
