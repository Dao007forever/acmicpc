#include <cstdio>

int a, b;

int f(int x) {
	int ret = 0, mul = 1;
	while (x) {
		int t = x % 10;
		if (t == 4 || t == 7) {
			ret = ret + t * mul;
			mul *= 10;
		}
		x /= 10;
	}
	return ret;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &a, &b);
	for (int i = a + 1; ; i++) {
		int tmp = f(i);
		if (tmp == b) {
			printf("%d\n", i);
			return 0;
		}
	}
}
