import os
import random
n = 10
m = 10
a = [-1] + [random.randint(0, 2 ** 30 - 1) for i in range(n)]
b = [-1]
res = []
with open("b.in", "w") as f:
    f.write("%d %d\n" % (n, m))
    for i in range(m):
        l = random.randint(1, n)
        r = random.randint(l, n)
        s = a[l]
        res.append((l, r, s))
        for i in range(l + 1, r + 1):
            s |= a[i]
        f.write("%d %d %d\n" % (l, r, s))
os.system("./b.ao < b.in > b.out")
with open("b.out") as f:
    l = f.readlines()
print(l)
a = list(map(int, l[1][:-1].split()))
assert(len(a) == n)
a = [-1] + a
for i in range(1, m + 1):
    ask = res[i]
    s = a[ask[0]]
    for i in range(ask[0] + 1, ask[1] + 1):
        s |= a[i]
    assert(s == ask[2])
