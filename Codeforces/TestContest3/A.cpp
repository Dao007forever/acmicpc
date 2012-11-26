#include <cstdio>

int n;
int a[222222];
int ans[222222];

int main() {
	freopen("in", "r", stdin);
	scanf("%d", &n);
	int sum = 0;
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]), sum += a[i];
	int cnt = 0;
	for (int i = 0; i < n; i++)
		if ((sum - a[i]) % (n - 1) == 0)
			if (a[i] == (sum - a[i]) / (n - 1))
				ans[cnt++] = i + 1;
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++)
		printf("%d ", ans[i]);
	return 0;
}
