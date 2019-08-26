

n, m = map(int, input().split())
f1 = n
f2 = n * (n - 1) >> 1
f3 = f2 * (n - 2) // 3
f4 = f3 * (n - 3) >> 2
fa = [0]
siz = [0]

for i in range(1, n + 1):
    fa.append(i)
    siz.append(1)
print(f4)


def find(x):
    global fa
    if x == fa[x]:
        return x
    fa[x] = find(fa[x])
    return fa[x]

def dele(x):
    global f1, f2, f3, f4
    f1 -= x
    f2 -= x * f1
    f3 -= x * f2
    f4 -= x * f3

def ins(x):
    global f1, f2, f3, f4
    f4 += x * f3
    f3 += x * f2
    f2 += x * f1
    f1 += x



for i in range(m):
    x, y = map(int, input().split())
    x = find(x);
    y = find(y);
    if x != y:
        dele(siz[x]);
        dele(siz[y]);
        siz[x] += siz[y]
        ins(siz[x]);
        fa[y] = x;
    print(f4)
