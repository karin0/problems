import os

s = 'set<'
for x in os.listdir():
    if x.endswith('.cpp'):
        vec = []
        with open(x) as fp:
            for l in fp:
                if s in l:
                    vec.append(l.strip())
        if vec:
            print(x)
            for l in vec:
                print(l)
