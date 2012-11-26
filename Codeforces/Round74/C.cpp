#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10000 + 10;
int n, m, k;
int a[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);
	}

	if (n % 2 == 0)
	{
		printf("0\n");
		return 0;
	}

	int Min = 10000000;
	for (int i = 1; i <= n; i++)
	if (i % 2 == 1)
	{
		Min = min(a[i], Min);
	}
	int temp = m / ((n + 1) / 2);
	long long res = min((long long)Min, (long long)k * temp);
	cout << res << endl;
	return 0;
}
