import functools

def a(x, y):
    if y > x or y < 0:
        return 0
    if y == 0:
        return 1
    return functools.reduce(lambda a, b: a * b, range(x - y + 1, x + 1))
n, m = map(int, input().split())

# print(a(n, n) * a(n + 1, m) * a(n + m + 1, 2) + a(n, n) * a(n + 1, m - 2) * a(m, 2) * 2 * a(n + m - 1, 1) + a(n, n) * a(n + 1, m - 4) * a(m, 4) * 2 * a(n + m - 3, 2))
print(a(n, n) * m * 2 * (n + 1) * a(n + 2, m - 1) + a(n, n) * a(n + 1, 2) * a(n + 3, m))
