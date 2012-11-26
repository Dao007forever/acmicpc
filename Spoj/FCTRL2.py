f = []
f.append(1L)
for i in range(1, 101):
	f.append(f[-1] * i)
re = input()
for ri in range(re):
	n = input()
	print f[n]
