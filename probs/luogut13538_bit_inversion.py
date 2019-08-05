import bisect
n = int(input())
a = list(map(int, input().split()))
arr = list(sorted(a))
ans = 0
brr = [-2, arr[0]]
for i in range(1, n):
    if arr[i] != arr[i - 1]:
        brr.append(arr[i])

vcnt = len(brr) - 1
lowbit = lambda x: x & -x
bit = [0] * (vcnt + 1)
def query(o):
    res = 0
    while o > 0:
        res += bit[o]
        o -= lowbit(o)
    return res
def update(o, x):
    while o <= vcnt:
        bit[o] += x
        o += lowbit(o)
for i in range(len(a)):
    x = bisect.bisect_left(brr, a[i])
    ans += (query(vcnt) - query(x)) * (n - i)
    update(x, i + 1)
print(ans)
