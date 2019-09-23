from math import gcd
from random import randint as rd
def f(a, b, c):
    p = gcd(a, b + c)
    q = gcd(a, b) + gcd(a, c)
    if p > 1:
        print(a, b, c, p, q)

mx = 10000000
for i in range(100000):
    f(*(rd(1, mx) for i in range(3)))