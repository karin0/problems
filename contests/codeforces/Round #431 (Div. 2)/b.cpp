#include <cstdlib>
#include <ctime>
#include <iostream>
using std::cin;
using std::cout;

const int MAXN = 1010;

int n, cnt, mcnt;
long long y[MAXN];
bool on[MAXN];
bool used[MAXN][MAXN];

int main() {
    std::ios::sync_with_stdio(false);
    srand((unsigned)time(0));
    long long i, a, b, vx, vx2, laston1, laston2;
    int o;
    long long vy, vy2;
    bool succ;
    cin >> n;
    mcnt = n * (n - 1);
    for (o = 1; o <= n; ++o) {
        cin >> y[o];
    }
    for (int tr = 1; tr <= 300 && cnt < mcnt; ++tr) {
        a = rand() % n + 1;
        b = rand() % n + 1;
        while (a == b || used[a][b]) {
            a = rand() % n + 1;
            b = rand() % n + 1;
        }
        used[a][b] = true;
        used[b][a] = true;
        cnt += 2;
        vx = a - b;
        vy = y[a] - y[b];
        laston1 = -1;
        laston2 = -1;
        on[a] = on[b] = true;
        for (i = 1; i <= n; ++i) {
            if (i == a || i == b)
                continue;
            if ((a - i) * vy == (y[a] - y[i]) * vx)
                on[i] = true;
            else
                on[i] = false, laston1 = laston2, laston2 = i;
        }
        if (laston1 == -1) {
            cout << (laston2 == -1 ? "NO\n" : "YEs\n");
            return 0;
        }
        vx2 = laston1 - laston2;
        vy2 = y[laston1] - y[laston2];
        if (vx * vy2 != vx2 * vy)
            continue;
        succ = true;
        for (i = 1; i <= n; ++i) {
            if (on[i] || i == laston1 || i == laston2)
                continue;
            if ((laston1 - i) * vy2 != (y[laston1] - y[i]) * vx2) {
                succ = false;
                break;
            }
        }
        if (succ) {
            cout << "Yes\n";
            return 0;
        }
    }
    cout << (cnt == mcnt ? "nO\n" : "No\n");
    return 0;
}
