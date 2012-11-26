#include <cstdio>

int n, k;
int a[2222];

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
		a[n + i] = a[i];
	}
	while (!a[k])
	{
		k++;
	}
	if (k > n) printf("%d\n", k - n);
	else printf("%d\n", k);
	return 0;
}
