from random import randint as ri
import os
mm = 10**3

while True:
    n = ri(1, mm)
    k = ri(1, mm)
    a = [ri(1, mm) for i in range(n)]
    with open('d.in', 'w') as f:
        f.write('%d %d\n' % (n, k))
        f.write(' '.join(map(str, a)) + '\n')
    os.system('./a.ao < d.in > d.out')

    with open('d.out', 'r') as f:
        ret = int(f.read())
    print(n, k)
    print(a)
    print(ret)
    ans = 0
    for i in range(n):
        for j in range(i, n):
            s = sum(a[i:j+1]) * k
            prod = 1
            for kk in range(i, j + 1):
                prod *= a[kk]
                if prod == s:
                    ans += 1
                    break
                if prod > s:
                    break
    print(ans)
    assert(ret == ans)
