col = int(raw_input())
while col:
	line = raw_input()
	result = []
	step = 0
	while step < col:
		cur = step
		while cur < len(line):
			result.append(line[cur])
			cur = cur + (2 * col - 1) - step * 2
			if cur < len(line):
				result.append(line[cur])
			cur = cur + step * 2 + 1
		step += 1
	print ''.join(result)
	col = int(raw_input())
