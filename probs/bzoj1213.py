#!/usr/bin/python2
m, n = input(), input()
l, r = 0, 1
while r ** m < n:
    l = r
    r *= 2

while (r - l > 1):
    mid = (l + r) >> 1
    x = mid ** m - n
    if (x <= 0):
        l = mid
        if (x == 0):
            break
    else:
        r = mid

print(l)
