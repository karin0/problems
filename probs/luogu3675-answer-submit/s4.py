import math
import os
import random
import time

def test(i, o, a):
    os.system('./checker %s %s %s >res 2>res' % (i, o, a))
    with open('res', 'r') as fp:
        x = fp.read()
    try:
        rr = float(x.split()[5][:-1])
        # rr = float(x.split()[1])
    except:
        rr = 0
    return rr * 10
random.seed(1926)
ss = 0
so = 0
def do(no):
    fin = 'mine%d.in' % no
    fnew = 'mine%d.new' % no
    fans = 'mine%d.ans' % no
    fout = 'mine%d.out' % no
    sold = test(fin, fout, fans)
    pts = []
    with open(fin, 'r') as rp:
        s, t, k1, k2, n = rp.readline().split()
        s, t, k1, k2 = map(float, (s, t, k1, k2))
        n = int(n)
        pos = s
        # print(s, t, k1, k2, n)
        for i in range(n):
            x, y, r, v = rp.readline().split()
            x, y, r = map(float, (x, y, r))
            v = int(v)
            if v > 0:
                for j in range(1 + int(random.random() * 6)):
                    pts.append((x, y, r, v))
    # random.shuffle(pts)
    pts.sort(key=lambda x: -x[3] + 0.5 * x[2] - random.random() * (x[0] * x[0] + x[1] * x[1]))
    with open(fnew, 'w') as fp:
        for p in pts:
            q = (math.atan2(p[1], p[0] - pos) / math.pi * 180)
            if 0.2 <= q <= 179.8:
                fp.write('g %.10f\n' % q)
            if random.random() > 0.99:
                pos = random.random() * s
                fp.write('m %.10f\n' % pos)
    snew = test(fin, fnew, fans)
    global ss
    global so
    ss += snew
    if snew > sold:
        print('Success, %f -> %f for %d\n' % (sold, snew, no))
        os.system('mv %s %s' % (fnew, fout))
        so += snew
    else:
        so += sold

for i in range(30):
    ss = 0
    so = 0
    for j in range(4, 11):
        do(j)
    print("#%d Got %f, best %f" % (i, ss, so))
