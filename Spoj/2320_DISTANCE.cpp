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

const int inf = 2000000000;
struct Point
{
	int x[6];
	void input(int d)
	{
		for (int i = 0; i < d; i++)
			scanf("%d", x + i);
	}
	int calDis(int mask, int d)
	{
		double res = x[d - 1];
		for (int i = 0; i < d - 1; i++)
		{
			if ((mask >> i) & 1) res += x[i];
			else res -= x[i];
		}
		return res;
	}
};
Point ps[100010];
int n, d;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &n, &d);
	for (int i = 0; i < n; i++)
		ps[i].input(d);
	int ans = -1;
	for (int mask = 0; mask < (1 << (d - 1)); mask++)
	{
		int maxDis = -inf, minDis = inf;
		for (int i = 0; i < n; i++)
		{
			int tmp = ps[i].calDis(mask, d);
			maxDis = max(maxDis, tmp);
			minDis = min(minDis, tmp);
		}
		ans = max(ans, maxDis - minDis);
	}
	printf("%d\n", ans);
	return 0;
}
