#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int N, H;
int f[55], d[55], t[55];
int now[55], ans[55], tmp[55], res;

void solve(int n, int time)
{
	memset(tmp, 0, sizeof(tmp));
	int tot = 0;
	for (int i = 1; i <= n; i++)
		now[i] = f[i];
	while (time > 0)
	{
		int Max = 0, k;
		for (int i = 1; i <= n; i++)
		if (now[i] > 0 && now[i] > Max)
		{
			Max = now[i];
			k = i;
		}
		if (Max == 0) k = 1;
		time -= 5;
		tmp[k] += 5;
		now[k] -= d[k];
		tot += Max;
	}
	if (tot >= res)
	{
		res = tot;
		memcpy(ans, tmp, sizeof(tmp));
	}
}

int main()
{
	freopen("a", "r", stdin);
	bool blank = false;
	while (scanf("%d", &N) && N)
	{
		if (blank) printf("\n");
		blank = true;
		scanf("%d", &H);
		H *= 60;
		for (int i = 1; i <= N; i++)
			scanf("%d", &f[i]);
		for (int i = 1; i <= N; i++)
			scanf("%d", &d[i]);
		for (int i = 1; i < N; i++)
			scanf("%d", &t[i]), t[i] *= 5;
		for (int i = 1; i < N; i++)
			t[i] += t[i - 1];
		res = 0;
		for (int k = N; k >= 1; k--)
		{
			solve(k, H - t[k - 1]);
		}
		for (int i = 1; i <= N; i++)
		if (i < N) printf("%d, ", ans[i]);
		else printf("%d\n", ans[i]);
		printf("Number of fish expected: %d\n", res);
	}
	return 0;
}
