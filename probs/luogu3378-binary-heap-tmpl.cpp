#include <akari>

IO<1000000, 1000000> io;

cint N = 1000002;

int a[N], siz;

inline void push(cint x) {
    int o = ++siz, f;
    a[o] = x;
    while (x < a[f = o >> 1]) {
        std::swap(a[o], a[f]);
        o = f;
    }
}
inline int front() {
    return a[1];
}
inline void pop() {
    std::swap(a[1], a[siz--]);
    int o = 1, x = a[1];
    while (true) {
        int p = o << 1;
        if (p > siz)
            return;
        if ((p | 1) <= siz && a[p | 1] < a[p])
            ++p;
        if (x <= a[p])
            return;
        std::swap(a[o], a[p]);
        o = p;
    }
}

int main() {
    int m = io;
    while (m--) {
        char op = io;
        switch (op) {
            case '1': push(io); break;
            case '2': io << front() daze; break;
            default:  pop();
        }
    }
}
