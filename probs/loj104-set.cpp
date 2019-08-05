#include <cstdio>
#include <climits>
#include <set>
#include <algorithm>
#include <iterator>

std::set<int> s;
int main() {
    static int m, opt, x;
    scanf("%d", &m);
    while (m--) {
        scanf("%d%d", &opt, &x);
        if (opt == 1)
            s.insert(x);
        else if (opt == 2)
            s.erase(x);
        else if (opt == 3)
            printf("%d\n", 1 + std::distance(s.begin(), s.lower_bound(x)));
        else if (opt == 4) {
            std::set<int>::iterator it = s.begin();
            std::advance(it, x - 1);
            printf("%d\n", *it);
        } else if (opt == 5) {
            printf("%d\n", *--s.lower_bound(x));
        } else if (opt == 6) {
            printf("%d\n", *s.upper_bound(x));
        }
    }
    return 0;
}
