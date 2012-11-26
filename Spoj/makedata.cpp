#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
	freopen("in", "w", stdout);
	int t = 1;
	while (t--)
	{
		int d, n, m;
		n = 50;
		m = 3;
		printf("%d %d\n", n, m);
		for (int i = 1; i <= n; i++)
		{
			int x = rand() % 123456, y = rand() % 45613;
			printf("%d %d\n", x, y);
		}
	}
	return 0;
}
