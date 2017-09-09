base = 141;
mod = 1e9 + 7;
def ha(s):
    h = [];
    x = 0;
    for i in range(len(s)):
        x = (x * base + ord(s[i])) % mod
        h.append(x)
    return h

print((ha("2333")[3] + (ord('$') - ord('3')) * base ** 2) % mod)
print(ha("2$33")[3])
