#include <cstdio>

int n;
int a[5555];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		a[x]++;
	}
	int ret = 0;
	for (int i = 1; i <= n; i++)
		if (!a[i]) ret++;
	printf("%d\n", ret);
	return 0;
}
