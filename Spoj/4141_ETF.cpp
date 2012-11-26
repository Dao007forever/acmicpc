#include <cstdio>

int n;

int Euler(int n) {
	int ret = 1;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			n /= i;
			ret *= (i - 1);
			while (n % i == 0)
				n /= i, ret *= i;
		}
	}
	if (n > 1) ret *= n - 1;
	return ret;
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		int ret = Euler(n);
		printf("%d\n", ret);
	}
	return 0;
}
