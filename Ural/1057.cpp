#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int f[32][32];
int X, Y, K, B;

void init()
{
	f[0][0] = 1;
	for (int i = 1; i <= 31; i++) {
		f[i][0] = f[i - 1][0];
		for (int j = 1; j <= i; j++)
			f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
	}
}

int calc(int x, int k)
{
	int tot = 0, ret = 0;
	for (int i = 31; i > 0; i--) {
		if (x & (1 << i)) {
			tot++;
			if (tot > k) break;
			x ^= (1 << i);
		}
		if ((1 << (i - 1)) <= x) {
			ret += f[i - 1][k - tot];
		}
	}
	if (tot + x == k) ret++;
	return ret;
}

int change(int x)
{
	int p = 1, tot = 0;
	while (x >= (long long)p * B) {
		p *= B;
		tot++;
	}
	int ret = 0;
	while (p && x / p <= 1) {
		ret += x / p * (1 << tot);
		tot--;
		x %= p;
		p /= B;
	}
	ret += (1 << (tot + 1)) - 1;
	return ret;
}

int main()
{
	init();
	scanf("%d%d%d%d", &X, &Y, &K, &B);
	printf("%d\n", calc(change(Y), K) - calc(change(X - 1), K));
	return 0;
}
