import sys

def gcd(a, b):
    return gcd(b, a % b) if b else a

g = 0
x = 0
y = 0
def exgcd(a, b):
    global g, x, y
    if b:
        exgcd(b, a % b)
        x, y = y, x
        y -= x * (a // b)
    else:
        g = a
        x = 1
        y = 0

n, m = map(int, input().split())

c1 = a1 = 0
for i in range(n):
    c2, a2 = map(int, input().split())
    if i:
        exgcd(c1, c2)
        t = a2 - a1
        if t < 0:
            t = -t
            x = -x
        tt = t // g
        if tt * g != t:
            print('he was definitely lying')
            sys.exit(0)
        c3 = c1 // g * c2
        a1 = (a1 + x * tt * c1) % c3
        if a1 < 0:
            a1 += c3
        c1 = c3
    else:
        c1 = c2
        a1 = a2

if a1 > m:
    print('he was probably lying')
else:
    print(a1)