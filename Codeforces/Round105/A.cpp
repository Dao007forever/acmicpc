#include <cstdio>
#include <cstring>

int a[5];
int vis[111111];
int main() {
	freopen("in.txt", "r", stdin);
	for (int i = 0; i < 4; i++)
		scanf("%d", &a[i]);
	int d;
	scanf("%d", &d);
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < 4; i++)
		for (int j = a[i]; j <= d; j += a[i])
			vis[j] = 1;
	int ret = 0;
	for (int i = 1; i <= d; i++)
		if (vis[i]) ret++;
	printf("%d\n", ret);
	return 0;
}
