from random import randint as rd
import os

def seq(n):
    return [rd(-1000, 1000) for i in range(n)]
def sseq(n):
    return ' '.join(map(str, seq(n)))
def napt(l):
    p = rd(1, l)
    if p == 1:
        t = rd(1, l - 1)
    else:
        t = rd(1, l - p + 1)
    return p, t
def pt(l):
    p = rd(1, l)
    t = rd(1, l - p + 1)
    return p, t

def do():
    n = rd(1, 10)
    m = rd(10, 20)
    print(n, m)
    l = n
    with open('a.in', 'w') as fp:
        fp.write('%d %d\n%s\n' % (n, m, sseq(n)))
        for i in range(m):
            op = rd(1, 6)
            if op == 1:
                p = rd(0, l)
                t = rd(1, 10)
                l += t
                fp.write('INSERT %d %d %s\n' % (p, t, sseq(t)))
            elif op == 2:
                if l > 1:
                    p, t = napt(l)
                    l -= t
                    fp.write('DELETE %d %d\n' % (p, t))
                else:
                    fp.write('MAX-SUM\n')
            elif op == 3:
                p, t = pt(l)
                fp.write('MAKE-SAME %d %d %d\n' % (p, t, rd(-1000, 1000)))
            elif op == 4:
                p, t = pt(l)
                fp.write('REVERSE %d %d\n' % (p, t))
            elif op == 5:
                p, t = pt(l)
                fp.write('GET-SUM %d %d\n' % (p, t))
            else:
                fp.write('MAX-SUM\n')
    if os.system('./a.ao < a.in > a.out'):
        raise ValueError

for i in range(1):
    do()
