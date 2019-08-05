#!/usr/bin/python2
db = {0: 0, 1: 1}
def f(x):
    if x <= 1:
        return x
    if x in db:
        return db[x]
    h = x >> 1
    if x & 1:
        y = f(h) + f(h + 1)
    else:
        y = f(h)
    db[x] = y
    return y

inp = lambda: int(raw_input())
t = inp()
for i in xrange(t):
    x = inp()
    print(f(x))
