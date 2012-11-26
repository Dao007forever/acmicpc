n = input()
m = []
for i in xrange(n):
	m.append(raw_input().split())
for name, s in m:
	if s == "rat": print name
for name, s in m:
	if s in["child", "woman"]: print name
for name, s in m:
	if s not in ["child", "woman", "rat", "captain"]: print name
for name, s in m:
	if s == "captain": print name
