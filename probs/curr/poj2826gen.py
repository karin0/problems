from random import randint as rd
import os
def do():
    with open('a.in', 'w') as fp:
        a = [rd(-10, 10) for i in range(4)]
        b = [rd(-10, 10) for i in range(4)]
        a = ' '.join(map(str, a))
        b = ' '.join(map(str, b))
        fp.write('1\n%s\n%s\n' % (a, b))
    os.system('./a.ao < a.in > a.out')
    os.system('./b.ao < a.in > a.ans')
    assert(os.system('diff -b a.out a.ans') == 0)

for i in range(1000):
    print(i)
    do()
    
