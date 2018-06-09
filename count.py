import os
mp = dict()
for oj in ('luogu', 'loj', 'uoj', 'bzoj', 'cf', 'poj', 'hdu', 'zoj', 'cv', 'noi'):
    mp[oj] = set()
os.chdir('probs')
for s in os.listdir():
    if any((s.endswith(t) for t in ('.cpp', '.cc', '.c', '.py', '.out'))):
        pres = [s[:s.find(t)] for t in ('.', '_', '-')]
        pres.sort(key = lambda t: len(t))
        pre = pres[0]
        for i in range(len(pre)):
            if pre[i].isdigit():
                break
        oj = pre[:i]
        pid = pre[i:]
        if oj.startswith('luogu'):
            pid = oj[5:] + pid
            oj = 'luogu'
        if oj in mp:
            mp[oj].add(pid)

for k in mp:
    print(k, len(mp[k]))
