from random import randint as rd
n = m = 20000
hf = 100
with open('t77.in', 'w') as fp:
    fp.write('%d %d\n' % (n, m))
    for i in range(m):
        l = rd(1, n)
        fp.write('1 %d %d %d\n' % (rd(1, n), rd(l, n), rd(1, 10000)))
