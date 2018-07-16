#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N = 1005;
int n, cur[N], st[N << 1], top;
struct point {
	int x, y;
	point() {}
	point(const int &x_, const int &y_) {
		x = x_;
		y = y_;
	}
	point operator-(const point &oth) const {
		return point(x - oth.x, y - oth.y);
	}
    ll operator * (const point &rh) const {
        return (ll)x * rh.y - (ll)y * rh.x;
    }
} p[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
	for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; ++j) {
            for (int k = j + 1; k <= n; ++k) {
                if ((p[i] - p[k]) * (p[j] - p[k]) == 0)
                    return 1;
            }
        }
	}
	return 0;
}
