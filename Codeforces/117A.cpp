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

int n, m;
int s, f, t;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d", &s, &f, &t);
		int T = 2 * (m - 1);
		if (s == f)
		{
			printf("%d\n", t);
			continue;
		}
		if (s < f)
		{
			int first = s - 1;
			int k;
			if (first >= t) k = 0;
			else
			{
				if ((t - first) % T == 0) k = (t - first) / T;
				else k = (t - first) / T + 1;
			}
			int ans = first + k * T + f - s;
			printf("%d\n", ans);
		}
		else
		{
			int first = 2 * m - s - 1;
			int k;
			if (first >= t) k = 0;
			else
			{
				if ((t - first) % T == 0) k = (t - first) / T;
				else k = (t - first) / T + 1;
			}
			int ans = first + k * T + s - f;
			printf("%d\n", ans);
		}
	}
	return 0;
}
