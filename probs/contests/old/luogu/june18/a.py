from math import pi, cos, sin
v, th = map(float, input().split())
vx = -v * sin(th)
vy = -v * cos(th)
t = vy / (-10.0)
x = -vx * t
y = 5 * t * t
print("%.5f %.5f" % (x, y))
