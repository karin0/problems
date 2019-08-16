from random import randint, seed
from os import system

while True:
    with open('a.in', 'w') as fp:
        n = randint(5, 5)
        m = randint(1, 5)
        a = [randint(1, 10) for i in range(n)]
        s = ' '.join(map(str, a))
        fp.write(f'{n} {m}\n{s}\n')
        for i in range(m):
            l = randint(1, n)
            r = randint(l, n)
            x = randint(1, 10)
            y = randint(x, 10)
            fp.write(f'{l} {r} {x} {y}\n')
    system('./a < a.in > a.out')
    system('./std < a.in > a.ans')
    if system('diff -b a.out a.ans'):
        break
