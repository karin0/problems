from random import randint, seed
from datetime import datetime
from os import system
import sys

seed(datetime.now())
for i in range(10000):
    n = randint(20, 20)
    s = ''.join((str(randint(0, 1)) for i in range(n)))
    print(s)
    with open('a.in', 'w') as fp:
        fp.write("1\n%s\n" % s)
    system('./a < a.in > a.out')
    '''print("Ans:")
    system('cat a.out')
    print('')'''
    system('./std < a.in > b.out')
    if system('diff -b a.out b.out'):
       sys.exit(1)