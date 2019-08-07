n = 8
a = [ [0 for i in range(n)] ] * n
for i in range(n):
    print(' '.join(map(str, a[i])))

i = 0
c = 0
while i < n:
    x = i
    y = 0
    if i == 3:
        while x >= 0 and y < n:
            print(x, y)
            a[x][y] = 1
            x -= 1
            y += 1
    i += 1


print("Done")
for i in range(n):
    print(' '.join(map(str, a[i])))
