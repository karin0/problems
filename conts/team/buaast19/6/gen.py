from random import randint, seed
from os import system
import datetime

k = 300

seed(datetime.datetime.now())
while True:
    n = randint(0, 100000)
    b = randint(1, 1000000000)
    a = ' '.join(map(str, (randint(0, 1) for i in range(n))))
    print(n, b)
    with open('a.in', 'w') as fp:
        fp.write(f'{n} {b}\n{a}\n')
    system('./a < a.in > a.out')
    system('cat a.out')
    system('./std < a.in > a.ans')
    system('cat a.ans')
    if system('diff -b a.out a.ans'):
        break
