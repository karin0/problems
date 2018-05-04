import os
import functools

def f(n):
    return functools.reduce(lambda x, y: x * y, map(int, list(str(n))))

def calc(k, n):
    res = 0
    for i in range(1, n + 1):
        y = f(i)
        if y <= k and y > 0:
            res += 1
    return res
def check(k, n):
    with open('t.in', 'w') as f:
        f.write('%d %d\n' % (k, n));
    os.system('./a.ao')
    with open('t.out') as f:
        out = int(f.readlines()[0][:-1])
    ans = calc(k, n)
    print("For k=%d, n=%d Out %d, ans %d" % (k, n, out, ans))
    if ans != out:
        print("BAD!!!")
        kkk = input()

i = 1
for j in range(10**5,10**6, 10000):
    check(i, j)
