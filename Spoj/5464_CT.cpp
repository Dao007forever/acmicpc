#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m;
long long ret;

int main()
{
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d", &n, &m);
		ret = 0;
		for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
		{
			int x = min(n - i, m - j), y = min(m - j, i) + 1;
			ret += (long long)x * y;
			x = min(i, j) + 1, y = min(m - j, i);
			ret += (long long)x * y;
			x = min(i, j), y = min(j, n - i) + 1;
			ret += (long long)x * y;
			x = min(n - i, m - j) + 1, y = min(j, n - i);
			ret += (long long)x * y;
		}
		cout << ret << endl;
	}
	return 0;
}
