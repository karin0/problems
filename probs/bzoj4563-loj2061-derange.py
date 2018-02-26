n = int(input())
a = [0, 0, 1]
if n > 2:
    for i in range(3, n + 1):
        a.append((i - 1) * (a[i - 1] + a[i - 2]))
print(a[n])
