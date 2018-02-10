#include <cstdio>
#include <algorithm>

typedef long long ll;
inline char gc() {
    static const int IN_LEN = 1000000;
    static char buf[IN_LEN], *s, *t;
    s == t ? t = (s = buf) + fread(buf, 1, IN_LEN, stdin) : 0;
    return s == t ? -1 : *s++;
}
template <class T>
inline void read(T &x){
    static char c;
    static bool neg;
    x = 0;
    for (c = gc(); c != '-' && (c < '0' || c > '9'); c = gc());
    if (c == '-')
        neg = true, c = gc();
    else
        neg = false;
    for (; c >= '0' && c <= '9'; c = gc())
        x = x * 10 + c - '0';
    if (neg)
        x = -x;
}

const int OUT_LEN = 1000000;
char obuf[OUT_LEN], *oh = obuf;
inline void pc(char c) {
    oh == obuf + OUT_LEN ? (fwrite(obuf, 1, OUT_LEN, stdout), oh = obuf) : 0;
    *oh++ = c;
}
template <class T>
inline void print(T x) {
    static int buf[30], cnt;
    if (x == 0) {
        pc('0');
    } else {
        if (x < 0)
            pc('-'), x = -x;
        for (cnt = 0; x; x /= 10)
            buf[++cnt] = x % 10 + 48;
        while (cnt)
            pc((char) buf[cnt--]);
    }
}
inline void flush() {
    fwrite(obuf, 1, oh - obuf, stdout);
}

int main() {
    static int n;
    static ll x, t;
    read(n);
    read(x), --n;
    while (n--)
        read(t), x = std::max(x, t);
    print(x);
    flush();
    return 0;
}
