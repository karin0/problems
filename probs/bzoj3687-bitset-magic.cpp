#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x) 0
    #define ccf(x) 0
    #define cccc(...) 0
#endif
typedef long long ll;

const int w = 2000000;
std::bitset<w + 1> s;
int main() {
    static int i, x;
    s.set(0);
    scanf("%d", &x);
    while (x--) {
        scanf("%d", &i);
        s ^= (s << i);
    }
    x = 0;
    rep (i, 0, w) if (s.test(i))
        x ^= i;
    printf("%d\n", x);

    return 0;
}
