import random
import os, datetime, sys

ri = random.randint

n = 10
m = 10
random.seed(datetime.datetime.now())
while True:
    with open('a.in', 'w') as fp:
        fp.write("%d %d\n" % (n, m))
        for i in range(m):
            u = ri(1, n)
            v = ri(1, n)
            l = ri(1, 100)
            r = ri(l, 100)
            fp.write(f"{u} {v} {l} {r}\n")

    os.system('cat a.in')
    os.system('./a < a.in > a.out')

    os.system('./std < a.in > a.ans')
    if os.system('diff -b a.out a.ans'):
        sys.exit(1)
