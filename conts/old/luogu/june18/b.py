ts = '''H	1
C	12
N	14
O	16
F	19
Na	23
Mg	24
Al	27
Si	28
P	31
S	32
Cl	35.5
K	39
Ca	40
Mn	55
Fe	56
Cu	64
Zn	65
Ag	108
I	127
Ba	137
Hf	178.5
Pt	195
Au	197
Hg	201'''.split()
tb = []
for i in range(len(ts) // 2):
    tb.append((ts[2 * i], ts[2 * i + 1]))
tb.sort(key=lambda x: -len(x[0]))

ans = 0
s = input()
p = s.find('~')
if p >= 0:
    t = s[p+1:]
    s = s[:p]
    if t[0] == 'H':
        ans = 18
    else:
        ans = 18 * int(t[:t.find('H')])
for p in tb:
    s = s.replace(p[0], '(%s)' % p[1])
while True:
    p = s.find('_{')
    if p < 0:
        break
    pp = s.find('}')
    s = s[:p] + '*%s' % s[p+2:pp] + s[pp+1:]
while ')(' in s:
    s = s.replace(')(', ')+(')
for i in range(0, 10):
    s = s.replace('%s('%i, '%s+('%i)
ans += eval(s)
x = int(ans)
if ans == x:
    print(x)
else:
    print('%s.5' % x)
