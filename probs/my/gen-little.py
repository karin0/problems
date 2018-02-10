from random import randint
import os
b = 10 ** 5
mo = 998244353
for i in range(1, 21):
    n = randint(2, b)
    a1 = randint(0, b)
    a2 = randint(0, b)
    p = randint(1, b)
    q = randint(1, b)
    with open("tst" + str(i) + ".in", "w") as f:
        f.write("%d\n%d %d %d %d\n" % (n, a1, a2, p, q))
    for j in range(3, n + 1):
        ans = (p * a2 % mo + q * a1 % mo) % mo
        a1, a2 = a2, ans
    print("#%d n = %d, ans = %d" % (i, n, ans))
    with open("tst" + str(i) + ".ans", "w") as f:
        f.write("%d\n" % ans)
    os.system("./a.ao < tst" + str(i) + ".in > tst" + str(i) + ".out")
    os.system("diff tst%d.out tst%d.ans" % (i, i))
