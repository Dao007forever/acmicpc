#include <cstdio>

int num[111], sum[111];
int n, a, b;

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d%d", &n, &a, &b);
	if (b == 0 && a > 0) {
		if (n == a + b + 1) {
			printf("-1\n");
			return 0;
		}
		num[0] = num[1] = 1;

		int i, k;
		for (i = 2, k = 0; k < a; i++, k++)
			num[i] = num[i - 1] + 1;
		for (; i < n; i++)
			num[i] = num[i - 1];
		for (int i = 0; i < n - 1; i++)
			printf("%d ", num[i]);
		printf("%d\n", num[n - 1]);
		return 0;
	}
	num[0] = 1;
	sum[0] = 1;
	for (int i = 1; i <= b; i++) {
		num[i] = sum[i - 1] + 1;
		sum[i] = sum[i - 1] + num[i];
	}
	for (int i = b + 1; i <= a + b; i++) {
		num[i] = num[i - 1] + 1;
	}
	for (int i = a + b + 1; i < n; i++)
		num[i] = num[i - 1];
	for (int i = 0; i < n - 1; i++)
		printf("%d ", num[i]);
	printf("%d\n", num[n - 1]);
	return 0;
}
