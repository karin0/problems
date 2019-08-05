#include <akari>

struct S {
    char var;
    int last;
};
struct Stack {
    S a[52];
    int cnt;
    S pop() {
        return a[--cnt];
    }
    void push(const S &x) {
        a[cnt++] = x;
    }
    bool empty() {
        return !cnt;
    }
    void clear() {
        cnt = 0;
    }
} sta;

char s[10], var[10], sx[10], sy[10];
bool used[256];
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int l, goal, cur = 0, ans = 0;
        scanf("%d%s", &l, s);
        if (s[2] == 'n')
            sscanf(s + 4, "%d", &goal); // O(n^w)
        else
            goal = 0;
        bool err = false;
        while (l--) {
            scanf("%s", s);
            if (s[0] == 'F') {
                scanf("%s%s%s", var, sx, sy);
                if (used[var[0]]) {
                    err = true;
                    break;
                }
                used[var[0]] = true;
                sta.push((S){var[0], cur});
                if (cur == -1)
                    continue;
                if (sx[0] == 'n') {
                    if (sy[0] != 'n')
                        cur = -1;
                } else {
                    if (sy[0] == 'n')
                        ++cur;
                    else {
                        int x, y;
                        sscanf(sx, "%d", &x);
                        sscanf(sy, "%d", &y);
                        if (x > y)
                            cur = -1;
                    }
                }
                ans = std::max(ans, cur); // here
            } else {
                if (sta.empty()) {
                    err = true;
                    break;
                }
                S x = sta.pop();
                cur = x.last;
                used[x.var] = false;
            }
        }
        if (!sta.empty())
            err = true;
        if (err) {
            puts("ERR");
            while (l-- > 0) {
                scanf("%s", s);
                if (s[0] == 'F')
                    scanf("%s%s%s", var, sx, sy);
            }
            sta.clear();
            std::fill(used + 'a', used + 'z' + 1, false);
        } else
            puts(ans == goal ? "Yes" : "No");
    }
    return 0;
}
