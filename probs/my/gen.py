from random import randint
import os
b = 10 ** 9
for i in range(4, 21):
    n = randint(2, b)
    a1 = randint(0, b)
    a2 = randint(0, b)
    p = randint(1, b)
    q = randint(1, b)
    with open("max" + str(i) + ".in", "w") as f:
        f.write("%d\n%d %d %d %d\n" % (n, a1, a2, p, q))
for i in range(1, 21):
    os.system("./a.ao < max" + str(i) + ".in > max" + str(i) + ".out")
