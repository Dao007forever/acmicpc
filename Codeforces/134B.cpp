#include <cstdio>
#include <algorithm>
using namespace std;

const int inf = 100000007;
int n;

int calc(int x, int y) {
	if (y % x == 0)
		if (x == 1) return y - 1;
		else return inf;
	return calc(y % x, x) + y / x;
}

int main() {
	scanf("%d", &n);
	int ret = inf;
	for (int i = 1; i <= n; i++)
		ret = min(ret, calc(i, n));
	printf("%d\n", ret);
	return 0;
}
