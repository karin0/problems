from random import randint, seed
from os import system

k = 300

while True:
    with open('a.in', 'w') as fp:
        r = randint(10, k)
        l = randint(10, r)
        print(l,r)
        fp.write(f'1\n{l} {r}\n')
    system('./a < a.in > a.out')
    system('./std < a.in > a.ans')
    if system('diff -b a.out a.ans'):
        break
