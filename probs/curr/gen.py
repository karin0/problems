from random import randint
N = 10 ** 5
p = 998244353
n = randint(1, N)
m = randint(1, N)
a = [randint(0, p - 1) for i in range(n)]
b = [randint(0, p - 1) for i in range(m)]
t = randint(1, N)
with open("a.in", 'w') as f:
    f.write('%d %d\n' % (n, m))
    f.write(' '.join(map(str, a)) + '\n')
    f.write(' '.join(map(str, b)) + '\n')
    f.write('%d\n' % t)
