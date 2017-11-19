import functools
print(functools.reduce(lambda x, y: x ^ y, [int(input()) for i in range(3000000)]))
