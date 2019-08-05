#include <cstdio>
#include <cmath>
typedef long long LL;
struct Vector {
    LL x, y;
    Vector(LL x, LL y): x(x), y(y) {}
    Vector(): x(0), y(0) {}
};
LL det(Vector& a, Vector& b) {
    return std::abs(a.x * b.y - a.y * b.x);
}
Vector operator - (Vector& a, Vector& b) {
    return Vector(a.x - b.x, a.y - b.y);
}

int main() {
    Vector v[3], v1, v2;
    scanf("%lld%lld%lld%lld%lld%lld", &v[0].x, &v[0].y, &v[1].x, &v[1].y, &v[2].x, &v[2].y);
    v1 = v[1] - v[0];
    v2 = v[2] - v[0];
    printf("%lld", det(v1, v2));

    return 0;
}
