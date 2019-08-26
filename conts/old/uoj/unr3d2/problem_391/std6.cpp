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
} p[N];
ll mult(const point &a, const point &b) {
	return (ll)a.x * b.y - (ll)a.y * b.x;
}
bool cmp(const point &e1, const point &e2) {
	return mult(e1 - p[1], e2 - p[1]) > 0;
}
bool cmpx(const point &e1, const point &e2) {
	return e1.x < e2.x || e1.x == e2.x && e1.y < e2.y;
}
ll dist(const point e1, const point e2) {
	ll dx = e1.x - e2.x, dy = e1.y - e2.y;
	return dx * dx + dy * dy;
}
ll ret[N << 1];

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &p[i].x, &p[i].y);
	for (int i = 2; i <= n; i++) {
        for (int j = 1; j < i; ++j) {
            ll x = dist(p[i], p[j]);
            ret[i] = std::max(ret[i], x);
            ret[j] = std::max(ret[j], x);
        }
	}
	sort(ret + 1, ret + n + 1);
	for (int i = 1; i <= n; i++) printf("%lld%c", ret[i], " \n"[i == n]);
	return 0;
}
