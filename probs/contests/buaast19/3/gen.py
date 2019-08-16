import random
import os, datetime, sys

n = 10
m = 10
random.seed(datetime.datetime.now())
while True:
    with open('a.in', 'w') as fp:
        fp.write("%d %d\n" % (n, m))
        for i in range(n):
            fp.write(''.join(map(str, (random.randint(0,1) for i in range(m)))) + '\n')

    os.system('cat a.in')
    os.system('./a < a.in > a.out')

    os.system('./std < a.in > a.ans')
    if os.system('diff -b a.out a.ans'):
        sys.exit(1)
