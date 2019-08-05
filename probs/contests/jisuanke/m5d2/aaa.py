import random
d = dict()
md = dict()
mmd = dict()
mmmd = dict()
m = 19260817
mm = 40000217
mmm = 40000223
n = 1000000
ub = 10 ** 10
cnt = 0
for i in range(n):
    x = random.randint(0, ub)
    if x in d:
        continue
    d[x] = True
    if x % m in md and x % mm in mmd and x % mmm in mmmd:
        cnt = cnt + 1
        continue
    md[x % m] = True
    mmd[x % mm] = True
    mmmd[x % mmm] = True
print(cnt)
