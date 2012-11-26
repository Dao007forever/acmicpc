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

const int MAXN = 1000 + 10;
int p[MAXN], rank[MAXN], num[MAXN];

int getfather(int x)
{
	if (p[x] != x) 
		p[x] = getfather(p[x]);
	return p[x];
}

int main()
{
	freopen("a", "r", stdin);
	for (int i = 1; i <= MAXN - 10; i++)
	{
		p[i] = i;
		num[i] = 0;
	}
	int u, v;
	while (scanf("%d%d", &u, &v) != EOF)
	{
		int pu = getfather(u), pv = getfather(v);
		if (pu != pv)
		{
			num[pu] += num[pv];
			p[pv] = pu;
		}
		++num[pu];
	}
	for (int i = 1; i <= MAXN - 10; i++)
	{
		if (p[i] == i && (num[i] & 1))
		{
			printf("0\n");
			return 0;
		}
	}
	printf("1\n");
	return 0;
}
