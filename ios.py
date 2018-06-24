#!/usr/bin/python3
import sys
def strip(s):
    a = [t.strip() for t in s.split('\n')]
    r = ''
    for i in range(len(a) - 1):
        r += a[i]
        if a[i][-1].isalpha() and a[i + 1][0].isalpha():
            r += ' '
    r += a[-1]
    a = [c for c in r]
    for i in range(len(a) - 1):
        if a[i] == ' ' and (not (a[i - 1].isalpha() and a[i + 1].isalpha())):
            a[i] = ''
    return ''.join(a)

# use raw string
with open(sys.argv[1], 'r') as f:
    s = f.read()
l = s.find('struct IO');
r = s.rfind('};') + 2;
t = s[:l] + strip(s[l:r]) + s[r:]
while True:
    p = t.find('/*')
    if p == -1:
        break
    else:
        q = t.find('*/')
        t = t[:p] + t[q + 2:]

print(t)
