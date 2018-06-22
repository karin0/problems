from random import randint as rd
import os
mn = -10000
mx = 10000
def do():
    with open('a.in', 'w') as fp:
        a = [rd(mn, mx) for i in range(4)]
        b = [rd(mn, mx) for i in range(4)]
        a = ' '.join(map(str, a))
        b = ' '.join(map(str, b))
        fp.write('1\n%s\n%s\n' % (a, b))
    os.system('./a.ao < a.in > a.out')
    with open('a.out', 'r') as fp:
        x = float(fp.read())
    return x

cnt = 0
ok = 0
while True:
    x = do()
    cnt += 1
    if x > 0:
        ok += 1
    print(ok, cnt, ok/cnt)
    
