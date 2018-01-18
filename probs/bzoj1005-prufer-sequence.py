mem = [1, 1]
def fact(x):
    if x < len(mem):
        return mem[x]
    for i in range(len(mem), x + 1):
        mem.append(mem[i - 1] * i)
    return mem[i]

n = int(input())
q = 1
m = 0
s = 0
for i in range(n):
    d = int(input())
    if d != -1:
        q = q * fact(d - 1)
        s = s + d - 1
        m = m + 1
p = 1
for i in range(s):
    p = p * (n - 2 - i)
print(p * (n - m) ** (n - 2 - s) // q)
