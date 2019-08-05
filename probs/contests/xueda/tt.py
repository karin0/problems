import functools
def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)
def lcm(a, b):
    return a * b // gcd(a, b)
a = [32, 48, 96]
g = functools.reduce(gcd, a)
b = [0]
for i in range(100):
    c = []
    for j in b:
        c.append(j)
    for j in c:
        for k in a:
            if not k - j in b:
                b.append(k - j)
b.sort()
print(b, all(list(map(lambda x: (x) % g == 0, b))), g)
