def calc(n, m):
	res = 1L
	if n == m or m == 0 return 1
	else:
		if m == 1 return n
		temp = 1L
		fac = n
		for i in range(m, 0, -1):
			temp *= i
			res *= fac
			fac -= 1
			if res % temp1 == 0:
				res /= temp1
				temp1 = 1
		return res

t = input()
while t:
	t -= 1
	n, k = int(raw_input().split())
	print calc(n - 1, m - 1)
