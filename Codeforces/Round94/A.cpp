#include <cstdio>

int n;
int a[111];

int main() {
	freopen("in", "r", stdin);
	scanf("%d", &n);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", a + i);
		sum += a[i];
	}
	int ans = 0;
	for (int i = 0; i < n; i++) {
		if ((sum - a[i]) % 2 == 0) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
