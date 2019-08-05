import os
def do(x):
    print('Test %d' % x)
    os.system('./checker mine%d.in mine%d.out mine%d.ans >res 2>res' % (x, x, x))
    with open('res') as fp:
        l = fp.read()
        print(l, end='')
        try:
            x = float(l.split()[1]) * 10
        except:
            x = 0
    return int(x)
    # os.system('cat a.txt')
res = 0
for i in range(1, 11):
    res += do(i)
print("Total", res)
