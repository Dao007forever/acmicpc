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

const int MAXN = 100000 + 10;
int n;
int L[MAXN], R[MAXN], cur[MAXN], data[MAXN];

inline bool cmp(int a, int b)
{
	return a > b;
}

int main()
{
	freopen("a", "r", stdin);
	int Test = 10;
	while (Test--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", data + i);
		int p = 0;
		for (int i = 0; i < n; i++)
		{
			int j = lower_bound(cur, cur + p, data[i]) - cur;
			if (j == p) p++;
			cur[j] = data[i];
			L[i] = j;
		}
		p = 0;
		for (int i = n - 1; i >= 0; i--)
		{
			int j = lower_bound(cur, cur + p, data[i], cmp) - cur;
			if (j == p) p++;
			cur[j] = data[i];
			R[i] = j;
		}

		int Max = 0;
		for (int i = 0; i < n; i++)
			if (L[i] + R[i] > Max) Max = L[i] + R[i];
		p = 0;
		for (int i = 0; i < n; i++)
			if (Max == L[i] + R[i])
				data[p++] = data[i];
		printf("%d\n", p);
		sort(data, data + p);
		for (int i = 0; i < p; i++)
			if (i == 0) printf("%d", data[i]);
			else printf(" %d", data[i]);
		printf("\n");
	}
	return 0;
}
