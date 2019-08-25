def f(n):
    a = list(range(1, n + 1))

    cnt = 0
    while a:
        cnt += 1
        t = a[-1]
        b = []
        for x in a:
            if t % x:
                b.append(x)
        a = b
    print(cnt)

for i in range(1, 20):
    f(i)