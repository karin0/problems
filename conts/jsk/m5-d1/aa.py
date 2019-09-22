def f(x):
    res = x
    while x:
        res += x % 10
        x //= 10
    return res

def g(x):
    print(f(x) - x)


