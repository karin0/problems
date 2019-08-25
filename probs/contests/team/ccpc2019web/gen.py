from random import randint, seed
from os import system
import datetime

k = 300

seed(datetime.datetime.now())
while True:
    # n = randint(0, 100000)
    # m = 500000
    # b = randint(1, 1000000000)
    # a = ' '.join(map(str, (randint(0, 1) for i in range(n))))
    # print(n, b)
    with open('a.in', 'w') as fp:
        T = 10
        print(T)
        fp.write(f'{T}\n')
        for i in range(T):
            fp.write(f'{randint(1, 5000)} 1 1\n')
    # system('./or < a.in > a.out')
    # system('cat a.out')
    system('./ds < a.in > a.outt')
    print("OK")
    system('./bf < a.in > a.ans')
    # system('cat a.ans')
    # if system('diff -b a.out a.ans'):
     #    break
    if system('diff -b a.outt a.ans'):
        break
