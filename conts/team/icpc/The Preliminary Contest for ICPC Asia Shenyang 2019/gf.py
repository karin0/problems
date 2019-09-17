from random import randint, seed
from os import system
from datetime import datetime

rd = randint

seed(datetime.now())

while True:
    n = rd(1, 1000)
    k = rd(1, 1000)
    a = ' '.join(map(str, (rd(1, 10) for i in range(n))))
    print(n, k)
    with open('a.in', 'w') as fp:
        fp.write(f'{n} {k}\n{a}\n')
    if system('./a < a.in > a.out'):
        break
    system('cat a.out')
    '''
    system('./bf < a.in > a.ans')
    system('cat a.ans')
    if system('diff -b a.out a.ans'):
        break

    '''
