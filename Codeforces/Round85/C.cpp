#include <cstdio>
#include <iostream>
using namespace std;

int a[111111];
int main()
{
	freopen("a", "r", stdin);
	int n, y;
	long long x;
	cin >> n >> x >> y;
	if (n > y)
	{
		printf("-1\n");
		return 0;
	}
	for (int i = 1; i < n; i++)
	{
		a[i] = 1;
		y--;
	}
	a[n] = y;
	long long sum = 0;
	for (int i = 1; i <= n; i++)
		sum += (long long)a[i] * a[i];
	if (sum < x) printf("-1\n");
	else
	{
		for (int i = 1; i <= n; i++)
			printf("%d\n", a[i]);
	}
	return 0;
}
