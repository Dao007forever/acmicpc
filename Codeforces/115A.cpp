#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int p[2222];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &p[i]);
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		int t = 0;
		for (int j = i; j != -1; j = p[j])
			t++;
		ans = max(ans, t);
	}
	printf("%d\n", ans);
	return 0;
}
