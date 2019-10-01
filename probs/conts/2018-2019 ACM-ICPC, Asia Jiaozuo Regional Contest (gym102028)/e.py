import math

n = 246
pri = []
np = [False] * (n + 1)
for i in range(2, n + 1):
    if not np[i]:
        pri.append(i)
    for j in pri:
        v = i * j
        if v > n:
            break
        np[v] = True
        if i % j == 0:
            break

T = int(input())
for ks in range(T):
    n = int(input())
    x = y = 1
    for i in pri:
        t = x * i
        if t > n:
            break
        x = t
        y *= i + 1
    g = math.gcd(x, y)
    print(f'{x // g}/{y // g}')