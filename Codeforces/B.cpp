#include <cstdio>

int n;
int a[111], cnt[111];

int main()
{
	freopen("in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i);
		cnt[a[i]]++;
	}
	int ans = 0;
	for (int i = 1; i <= 100; i++)
		cnt[i] /= 2, ans += cnt[i];
	ans /= 2;
	printf("%d\n", ans);
	return 0;
}

