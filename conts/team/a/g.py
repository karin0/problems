from cyaron import *
from random import randint as ri

io = IO(file_prefix='a', data_id=0)

n = 300000

io.input_writeln(5)
for i in range(5):
    graph = Graph.graph(n, n)
    m = n
    io.input_writeln(n, m, repeated_edges=False, self_loop=False)
    io.input_writeln(graph.to_str(output=Edge.unweighted_edge))