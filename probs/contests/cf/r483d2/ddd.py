def f(a):
    m = len(a) - 1;
    b = [None]
    for i in range(1, m):
        c = list(sorted(a[i] + a[i + 1]))
        '''
        while True:
            flag = False
            for j in range(len(c) - 1):
                if c[j] == c[j + 1]:
                    x = c[j]
                    c.remove(x)
                    c.remove(x)
                    flag = True
                    break
            if not flag:
                break*/'''
        b.append(c)
    return b
def g(n):
    print("n=",n)
    a = [None] + [[i] for i in range(1, n + 1)]
    while len(a) > 2:
        a = f(a)
    b = [None] + a[1]
    c = [None]
    for i in range(1, n + 1):
        c.append(b.count(i))
    return c
    '''r = (len(b) - 1) // 2
    print(r, b)
    if not (list(range(1, r + 1)) == b[1:r+1]):
        print("wrong")
    if not (list(range(n-r+1,n+1)) == b[-r:]):
        print("wrong2")
    return r'''

a = [None, [1], [2], [3], [4], [5], [6]]
