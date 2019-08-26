def test(n, k):
    c1 = c2 = 0
    while n:
        if n < k:
            c1 += n
            break
        n -= k
        c1 += k
        t = n // 10
        #print(t)
        c2 += t
        n -= t
    # print(n, k, c1, c2)
    return c1 >= c2
def test2(n, k):
    c1 = c2 = 0
    while n:
        if n < k:
            c1 += n
            break
        n -= k
        c1 += k
        t = n // 10
        print(t)
        c2 += t
        n -= t
    # print(n, k, c1, c2)
    return c1 >= c2

def calc(n):
    for k in range(1, n + 1):
        if test(n, k):
            return k

cnt = dict()
for i in range(10000, 11001):
    f = calc(i)
    if f in cnt:
        cnt[f] += 1
    else:
        cnt[f] = 1
    test2(i, f)
    print(i, calc(i))
print(cnt)
