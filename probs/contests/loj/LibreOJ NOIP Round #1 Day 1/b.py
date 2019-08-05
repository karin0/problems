import random
def check(a, b, k):
    n = 300
    res = -1
    rs = None
    for i in range(n):
        t = k * a + b
        print("a%d = %d" % (i + 2, t))
        if t < b:
            # print("%d down to %d" % (i + 2, t))
            res = i + 2
            rs = t
        a = b
        b = t
    return res,rs

m = -1
for i in range(100):
    a, b, k = map(int, input().split())
    '''a = random.randint(-10000000, 10000000)
    b = random.randint(-10000000, 10000000)
    k = random.randint(1, 1000)'''
    if a * b >= 0:
        continue
    r = check(a, b, k)
    print(a, b, k, "->", r, r[1] < 2 ** 63)
print(m)
