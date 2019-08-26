from random import randint, seed
from os import system
from datetime import datetime

rd = randint

seed(datetime.now())

while True:
    with open('a.in', 'w') as fp:
        T = 10
        print(T)
        fp.write(f'{T}\n')
        for i in range(T):
            n = rd(1000, 100000)
            fp.write(f'{n}\n')
            for j in range(n - 1):
                fp.write(f'{j+1} {j+2}\n')
            m = rd(100000, 200000)
            fp.write(f'{m}\n')
            for j in range(m):
                op = rd(1, 2)
                if op == 1:
                    fp.write(f'1 {rd(1, n)}\n')
                else:
                    fp.write(f'2 {rd(1, n)} {rd(1, n)}\n')
            # a = ' '.join(map(str, (rd(0, 1) for i in range(n))))
            # print(n, m, a)
            # fp.write(f'{rd(1, 5000)} 1 1\n')
    break
    system('./a < a.in > a.out')
    system('cat a.out')
    system('./bf < a.in > a.ans')
    system('cat a.ans')
    if system('diff -b a.out a.ans'):
        break
