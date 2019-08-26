e = '__'
def show(a):
    s = ''
    for i in range(1, len(a)):
        t = str(a[i])
        if t != e and len(t) == 1:
            t = '0' + t
        s += t + ' '
    print(s)
def foo(n):
    a = [e] * (2 * n)
    for i in range(1, n + 1):
        a[2 * i - 1] = str(i);
    show([i for i in range(len(a))])
    cnt = 0
    while True:
        show(a)
        i = j = 0
        for i in range(len(a) - 1, 0, -1):
            if a[i] != e:
                break
        for j in range(i - 1, -1, -1):
            if a[j] == e:
                break
        if j == 0:
            break
        a[i], a[j] = a[j], a[i]
        cnt += 1
    show(a)
    return a

l = foo(8)
#for k in range(100):
#    print(k, foo(k))
