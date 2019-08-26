from random import randint as rd
import os
n = 10
m = rd(1, n)
def do():
    with open('t4.in', 'w') as fp:
        fp.write('%d %d\n' % (n, m))
        a = []
        x = 0
        for i in range(n):
            a.append(rd(0, 10))
            '''if i & 1:
                x += rd(1, 500)
            elif x > 0:
                x -= rd(1, x // 2)'''
        fp.write('%s\n' % ' '.join(map(str, a)))
    os.system('./a4 < t4.in > t4.out')
    os.system('./a.ao < t4.in > t4.ans')
    assert(not os.system('diff t4.out t4.ans'))

while True:
    do()
    print("AC")
