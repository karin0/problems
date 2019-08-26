#include <cstdio>
#include <algorithm>
#include <queue>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))

typedef long long ll;
const int N = 200005;
std::priority_queue<int, std::vector<int>, std::greater<int> > q0, q1;
std::vector<int> l[N];
char s[N];
int k;
bool failed;
int main() {
    static int i, j, x;
    scanf("%s", s + 1);
    for (i = 1; s[i]; ++i) {
        x = s[i] - '0';
        if (x == 0) {
            if (q1.empty()) {
                l[k].push_back(i);
                q0.push(k++);
            } else {
                j = q1.top();
                q1.pop();
                l[j].push_back(i);
                q0.push(j);
            }
        } else {
            if (q0.empty()) {
                failed = true;
                break;
            }
            j = q0.top();
            q0.pop();
            l[j].push_back(i);
            q1.push(j);
        }
    }
    if (failed) {
        puts("-1");
        return 0;
    }
    for (i = 0; i < k; ++i) {
        if (s[l[i].back()] == '1') {
            puts("-1");
            return 0;
        }
    }
    printf("%d\n", k);
    for (i = 0; i < k; ++i) {
        printf("%d", (int)l[i].size());
        for (std::vector<int>::iterator it = l[i].begin(); it != l[i].end(); ++it)
            printf(" %d", *it);
        putchar('\n');
    }

    return 0;
}
