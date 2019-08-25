import random

n = 100
a = list(range(1, n + 1))
random.shuffle(a)
f = open('b.in', 'w')
f.write('%d\n' % n)
for i in a:
    f.write("%d "% i)
f.write('\n')
f.close()
