#include <cstdio>

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

int pow(int a, int x) {
	int ret = 1;
	for (; x; x >>= 1) {
		if (x & 1) ret = ret * a;
		a = a * a;
	}
	return ret;
}

int polya(int c, int n) {
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		ret += pow(c, gcd(i, n));
	}
	if (n & 1) {
		ret += n * pow(c, n / 2 + 1);
	}else {
		ret += pow(c, n / 2) * n / 2 + pow(c, n / 2 + 1) * n / 2;
	}
	return ret / 2 / n;
}

int main() {
	freopen("in.txt", "r", stdin);
	int c, n;
	while (scanf("%d%d", &c, &n)) {
		if (c == 0 && n == 0) break;
		printf("%d\n", polya(c, n));
	}
	return 0;
}
