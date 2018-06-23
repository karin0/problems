from random import randint as rd

def do():
    ks = 20
    n = 100000
    with open('a.in', 'w') as fp:
        fp.write('%d\n' % ks)
        for i in range(ks):
            fp.write('%d\n%s\n' % (n, ' '.join(map(str, (rd(1, 100000) for j in range(n))))))

do()
