from math import *
def ispri(x):
    if x <= 1:
        return False
    if x == 2:
        return True
    for i in range(2, int(ceil(sqrt(x))) + 1):
        if x % i == 0:
            return False
    return True

cnt = 0
ind = dict()
a = []
for i in range(2, 100000):
    if ispri(i):
        ind[i] = cnt
        a.append([i, 0])
        cnt = cnt + 1
def f(x):
    res = dict()
    i = 2
    while i * i <= x:
        if x % i == 0:
            x //= i
            res[i] = 1
            while x % i == 0:
                x //= i
                res[i] += 1
        i += 1
    if x > 1:
        res[x] = 1
    return res
                

for i in range(2, 100000):
    res = f(i).items()
    for k, v in res:
        a[ind[k]][1] += v
    last = 1 << 31
    for j in a:
        if j[1] > last:
            print("Fail")
            a()
        last = j[1]
    print(i)
