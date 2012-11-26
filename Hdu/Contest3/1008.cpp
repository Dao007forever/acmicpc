#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define abs(x) ((x) > 0 ? (x) : -(x))
int n, m;
vector<int> vec[111];

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &n, &m))
	{
		if (n == 0 && m == 0) break;
		for (int i = 1; i <= n; i++)
			vec[i].clear();
		for (int i = 1; i <= n * n; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			vec[x].push_back(y);
		}
		for (int i = 1; i <= n; i++)
			sort(vec[i].begin(), vec[i].end());
		int ans = 1000000000;
		for (int j = 1; j + n - 1 <= m; j++)
		{
			int sum = 0;
			for (int i = 1; i <= n; i++)
			{
				for (int k = 0; k < n; k++)
				{
					sum += abs(j + k - vec[i][k]);
				}
			}
			ans = min(ans, sum);
		}
		printf("%d\n", ans);
	}
	return 0;
}
