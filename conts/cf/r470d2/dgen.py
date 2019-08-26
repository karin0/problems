from cyaron import *

n = 300000
mx = 2**30 - 1
vec1 = Vector.random(n, [(1, mx)], 1)
vec2 = Vector.random(n, [(1, mx)], 1)
io = IO('d.in', 'd.out')
io.input_writeln(n)
io.input_writeln(vec1)
io.input_writeln(vec2)
