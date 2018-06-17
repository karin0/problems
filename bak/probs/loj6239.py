def f(x):
    res = x
    while x:
        res += x % 10
        x //= 10
    return res
n = int(input())
cnt = 0
ans = []
for i in range(max(0, n - 100), n):
    if f(i) == n:
        cnt += 1
        ans.append(i)
        if cnt >= 2:
            break
print(cnt)
for i in ans:
    print(i)
