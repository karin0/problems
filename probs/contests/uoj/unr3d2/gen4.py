from random import randint as rd
n = 100000
m = 1000
with open('t4.in', 'w') as fp:
    fp.write('%d %d\n' % (n, m))
    a = []
    x = 0
    for i in range(n):
        assert(0 <= x <= 1000000000)
        a.append(x)
        if i & 1:
            x += rd(1, 500)
        elif x > 0:
            x -= rd(1, x // 2)
    fp.write('%s\n' % ' '.join(map(str, a)))
