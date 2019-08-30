import string, itertools, sys, copy, re

nums = set({0, 1})
def pp(s):
    i = s.find('1')
    if i < 0:
        return s
    j = i + 1
    l = len(s)
    while j < l and (s[j] == '0' or s[j] == '1'):
        j += 1
    return pp(s[:i]) + str(int(s[i:j], 2)) + pp(s[j:])
def proc(s):
    if not s:
        return None
    # print("s = ",s)
    try:
        if '()' in s:
            raise ValueError
        if '=' in s:
            raise ValueError
        if '**' in s:
            raise ValueError
        if s[0] == '+':
            raise ValueError
        if '-+' in s:
            raise ValueError
        if '*+' in s:
            raise ValueError
        if '++' in s:
            raise ValueError
        if '(+' in s:
            raise ValueError
        if s.startswith('00'):
            raise ValueError
        if '+00' in s:
            raise ValueError
        if '-00' in s:
            raise ValueError
        if '*00' in s:
            raise ValueError
        if '(00' in s:
            raise ValueError
        if s.startswith('01'):
            raise ValueError
        if '+01' in s:
            raise ValueError
        if '-01' in s:
            raise ValueError
        if '*01' in s:
            raise ValueError
        if '(01' in s:
            raise ValueError
        r = eval(pp(s))
        if not isinstance(r, int):
            return None
        return r
    except:
        return None

symbs = ['0', '1', '+', '-', '*', '(', ')']
s = input()
sig = set(s)
lets = sig.intersection(set(string.ascii_letters))
cnt = len(lets)
if cnt > 8 or s[0] == '=' or s[-1] == '=':
    print("0")
    sys.exit(0)

eqi = s.find('=')
if cnt == 0:
    s1 = proc(s[:eqi])
    if s1 is None:
        print(0)
        sys.exit(0)
    s2 = proc(s[eqi + 1:])
    if s2 is None:
        print(0)
        sys.exit(0)
    if s1 == s2:
        print(1)
    else:
        print(0)
    sys.exit(0)

if eqi >= 0:
    if s.count('=') > 1:
        print(0)
        sys.exit(0)
    ans = 0
    ns = list(lets)
    for p in itertools.permutations(symbs, cnt):
        expr = s
        for i in range(cnt):
            expr = expr.replace(ns[i], p[i])
        s1 = proc(expr[:eqi])
        if s1 is None:
            continue
        s2 = proc(expr[eqi + 1:])
        if s2 is None:
            continue
        # print(expr, s1, "=", s2)
        if s1 == s2:
            ans += 1
    print(ans)
    sys.exit(0)


ls = list(s)
ans = 0
for c in lets:
    if s[0] == c or s[-1] == c:
        continue
    cc = ls.count(c)
    if cc != 1:
        continue
    eqi = ls.index(c)
    ns = copy.deepcopy(lets)
    ns.remove(c)
    ns = list(ns)
    ccc = cnt - 1
    for p in itertools.permutations(symbs, ccc):
        expr = s
        for i in range(ccc):
            expr = expr.replace(ns[i], p[i])
        s1 = proc(expr[:eqi])
        if s1 is None:
            continue
        s2 = proc(expr[eqi + 1:])
        if s2 is None:
            continue
        if s1 == s2:
            ans += 1
print(ans)
