#!/usr/bin/python2
n = int(raw_input())
a = 1
b = 5
x = 0
for i in range(3, n + 1):
    # a = f[i - 2], b = f[i - 1]
    x = b * 3 - a + 2
    a = b
    b = x

print(b)
