def fac(n):
    ans = 1
    for i in range(2, n + 1):
        ans *= i
    return ans
def cal(x, lft):
    print(x, lft)
    rr = 1
    re = 1
    flf = fac(lft)
    for i in range(1, x + 1):
        re *= x - i + 1
        rr += re * ((i + 1) ** lft)
    return rr * flf
s = input()
cnt = [0] * 10
for c in s:
    cnt[int(c)] += 1
# print(cnt)
ss = sum(cnt)
lft = 0
for i in range(10):
    if cnt[i] > 0:
        ss -= 1
        lft += 1
ans = cal(ss, lft)
for i in range(10):
    if cnt[i] > 0:
        ans //= fac(cnt[i])
if cnt[0] > 0:
    cnt[0] -= 1
    t = cal(ss, lft - 1)
    for i in range(10):
        if cnt[i] > 0:
            t //= fac(cnt[i])
    print('ans',ans,'t',t);
    ans -= t
print(ans)
