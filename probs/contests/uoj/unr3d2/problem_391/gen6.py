import os
import time
from math import cos, sin, pi
from random import random, seed
seed(time.time())

def do():
    n = 200
    nn = 0
    a = set()
    cntx = dict()
    cnty = dict()
    r = 1e8
    for i in range(n):
        t = random() * 2 * pi
        x = int(cos(t) * r)
        if x in cntx:
            if cntx[x] >= 2:
                continue
            else:
                cntx[x] += 1
        else:
            cntx[x] = 1
        y = int(sin(t) * r)
        if y in cnty:
            if cnty[y] >= 2:
                continue
            else:
                cnty[y] += 1
        else:
            cnty[y] = 1
        p = (x, y)
        if p not in a:
            a.add(p)
            nn += 1
    with open('t6.in', 'w') as fp:
        fp.write('%d\n' % nn)
        for p in a:
            fp.write('%d %d\n' % (p[0], p[1]))
    if os.system('./val6 < t6.in'):
        print('bad in')
        return
    os.system('./a6 < t6.in > t6.out')
    os.system('./a.ao < t6.in > t6.ans')
    assert(not os.system('diff t6.out t6.ans'))
    print('ac')
for i in range(10000):
    do()
