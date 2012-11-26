n, m, k, t = map(int, raw_input().split())
crops = ["Carrots", "Kiwis", "Grapes"]
waste = []
for i in xrange(k):
	a, b = map(int, raw_input().split())
	a -= 1
	b -= 1
	waste.append(a * m + b)
for i in xrange(t):
	a, b = map(int, raw_input().split())
	a -= 1
	b -= 1
	place = a * m + b
	num = 0
	for w in waste:
		if w == place:
			num = -1
			break
		if w < place:
			num += 1
	if num == -1:
		print "Waste"
	else:
		print crops[(place - num) % 3]
