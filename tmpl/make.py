import os

srcs = [
    "Miller–Rabin.cpp"
]

srcs = filter(lambda s: s.endswith('.cpp'), os.listdir())

with open('out.md', 'w') as ofp:
    ofp.write('[toc]\n\n')
    for fn in srcs:
        print(fn)
        ofp.write(f"## {fn[:fn.rfind('.')]}\n\n```c++\n")
        t = ''
        with open(fn) as sfp:
            for l in sfp:
                if '#include' in l and '<akari>' in l:
                    continue
                if 'tmpl_end' in l:
                    break
                t += l
        ofp.write(f'{t.rstrip()}\n```\n\n')
