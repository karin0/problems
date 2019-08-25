n, m = list(map(int, input().split()))
l = [-1] + list(map(int, input().split()))
s = [0]
for i in range(n):
    s.append(s[-1] + l[1 + i])
for i in range(m):
    w, a, b, c = map(int, input().split())
    print(s[b] - s[a - 1])
