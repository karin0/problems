a = int(input())
b = int(input())
a = 10 ** 10000
b = 40 ** 10000
print(__import__('fractions').gcd(a, b))
